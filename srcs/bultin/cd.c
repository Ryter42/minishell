/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:22:09 by elias             #+#    #+#             */
/*   Updated: 2023/10/31 18:35:02 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*new_var(char *name, char *value)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	// free(value);
	return (res);
}

char	**change_var(char *var_name, char *var_value, char **env)
{
	char **res;
	int	i;
	// int	test;

	// test = 1;
	i = 0;
	res = malloc(sizeof(char *) * (strllen(env) + 1));
	// printf("len de env = %d\n", strllen(env));
	while (env[i])
	{
		if (!ft_strncmp(var_name, env[i], ft_strlen(var_name)) && env[i][ft_strlen(var_name)] == '=')
		{
			res[i] = new_var(var_name, var_value);
			// printf("i = %d\n", i);
			i++;
			// test = 0;
		}

		else
		{
			res[i] = env[i];
			// printf("i = %d\n", i);
			i++;
		}
	}
		// printf("i = %d\n", i);
	res[i] = 0;
	free(env);
	return (res);
}

// void	go_home(t_cmd *cmd)
// {
// 	char	*buff;

// 	buff = NULL;
// 	getcwd(buff, 0);
// 	change_var("OLDPWD", buff, cmd->data->env);
// 	if (!chdir(find_var(cmd->data->env, "HOME", 4)))
// 		perror(find_var(cmd->data->env, "HOME", 4));
// 	getcwd(buff, 0);
// 	change_var("PWD", buff, cmd->data->env);
// }

// void	go_path(t_cmd *cmd)
// {
// 	char	*buff;

// 	buff = NULL;
// 	getcwd(buff, 0);
// 	change_var("OLDPWD", buff, cmd->data->env);
// 	if (!chdir(cmd->arg[1]))
// 		perror(cmd->arg[1]);
// 	getcwd(buff, 0);
// 	change_var("PWD", buff, cmd->data->env);
// }

char	*path_to_home(char *home, char *path)
{
	if (!path)
		return (home);
	else
		return (ft_strjoin(home, path + 1));
}

void	cd(t_cmd *cmd)
{
	char	*buff1;
	char	*buff2;

	buff1 = NULL;
	buff2 = NULL;
	buff1 = getcwd(buff1, 0);
	dprintf(2, "cd\n");
	if (!cmd->arg[1] || cmd->arg[1][0] == '~')
	{
		if (chdir(path_to_home(find_var(cmd->data->env, "HOME", 4), cmd->arg[1])) == -1)
		{
			perror(path_to_home(find_var(cmd->data->env, "HOME", 4), cmd->arg[1]));
			return ;	
		}
	}
	else
	{
		if (chdir(cmd->arg[1]) == -1)
		{
			perror(cmd->arg[1]);
			return ;
		}
	}
	buff2 = getcwd(buff2, 0);
	cmd->data->env = change_var("OLDPWD", buff1, cmd->data->env);
	cmd->data->env = change_var("PWD", buff2, cmd->data->env);
}