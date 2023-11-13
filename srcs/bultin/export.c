/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:22:54 by elias             #+#    #+#             */
/*   Updated: 2023/11/01 00:11:12 by elias            ###   ########.fr       */
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

int	valid_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
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
	int	i;
	char **res;

	i = 0;
	res = malloc(sizeof(char *) * (strllen(env) + 2));
	while (env[i])
	{
		res[i] = env[i];
		i++;
	}
	res[i] = arg;
	i++;
	res[i] = 0;
	if (arg)
		free(env);
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
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

void	export(t_cmd *cmd)
{
	int	i;
	// char	**new_env;
	dprintf(2, "export\n");

	i = 1;
	if (!cmd->arg[1])
		print_sort_tab(cmd->data->env);
	else if (cmd->arg[i][0] == '-')
	{
		printf("bash: export: %c%c: invalid option", cmd->arg[1][0], cmd->arg[1][1]);
		return ;
	}
	while (cmd->arg[i])
	{
		if (valid_export(cmd->arg[i]))
			cmd->data->env = cpy_env_with(cmd->data->env, cmd->arg[i]);
		i++;
	}
}