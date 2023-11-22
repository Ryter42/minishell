/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:22:54 by elias             #+#    #+#             */
/*   Updated: 2023/11/22 20:02:15 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unvalid_char(char c)
{
	if (c == '%' || c == '$' || c == '#' || c == '@' || c == '^' || c == '*' || c == ':')
		return (1);
	else
		return (0);
}

// int	valid_export(char *arg)
// {
// 	int	i;

// 	i = 0;
// 	if (arg[0] == '=')
// 	{
// 		printf("minishell: export: `%s': not a valid identifier\n", arg);
// 		return(0);
// 	}
// 	while (arg[i] && arg[i] != '=' && !unvalid_char(arg[i]))
// 		i++;
// 	if (arg[i] == '=')
// 		return (1);
// 	else if (!arg[i])
// 		return (0);
// 	else
// 	{
// 		printf("minishell: export: `%s': not a valid identifier\n", arg);
// 		return (0);
// 	}
// }

int	valid_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || ft_isdigit(arg[0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return(0);
	}
	while (arg[i] && arg[i] != '=' && !unvalid_char(arg[i]))
		i++;
	if (arg[i] == '=')
		return (1);
	else if (!arg[i])
		return (0);
	else
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (0);
	}
}

char	**cpy_env_with(char **env, char *arg)
{
	int		i;
	int 	add;
	char	**res;

	if (arg)
		add = 1;
	else
		add = 0;
	i = 0;
	res = malloc(sizeof(char *) * (strllen(env) + 1 + add));
	while (env[i])
	{
		res[i] = ft_strdup(env[i]);
		i++;
	}
	if (arg)
	{
		res[i] = ft_strdup(arg);
		i++;
	}
	res[i] = 0;
	if (arg)
		free_tab(env);
	return (res);
}

// int	ordre_alpha(char *str1, char *str2)
// {

// }

char	**sort_tab(char **tab)
{
	char *str;
	int	i;

	i = 0;
	while (tab[i + 1])
	{
		if (ft_strncmp(tab[i], tab[i + 1], ft_strlen(tab[i])) < 0)
			i++;
		else
		{
			str = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = str;
			i = 0;
		}
	}
	return (tab);
}

void	print_sort_tab(char **tab)
{
	int	i;

	i = 0;
	tab = sort_tab(tab);
	while (tab[i])
	{
		if (ft_print_str("declare -x ") == -1)
		{
			write(2, "export: write error: No space left on device\n", 45);
			return ;
		}
		ft_print_str(tab[i]);
		ft_print_str("\n");
		// printf("declare -x %s\n", tab[i]);
		i++;
	}
}

void	export(t_cmd *cmd)
{
	int	i;
	// char	**new_env;
	// printf("export\n");

	// printf("address de data dans export = %p\n", cmd->data);
	i = 1;
	if (!cmd->arg[1])
		print_sort_tab(cmd->data->env);
	else if (cmd->arg[1][0] == '-')
	{
		if (!cmd->arg[1][1])
			write(2, "minishell: export: `-': not a valid identifier\n", 47);
			// printf("minishell: export: `-': not a valid identifier\n");
		else
		{
			write(2, "minishell: export: ", 19);
			write(2, &cmd->arg[1][0], 1);
			write(2, &cmd->arg[1][1], 1);
			write(2, ": invalid option\n", 17);
		}
			// printf("minishell: export: %c%c: invalid option\n", cmd->arg[1][0], cmd->arg[1][1]);
		return ;
	}
	while (cmd->arg[i])
	{
		if (valid_export(cmd->arg[i]))
			cmd->data->env = cpy_env_with(cmd->data->env, cmd->arg[i]);
		i++;
	}
}