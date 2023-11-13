/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:25:41 by elias             #+#    #+#             */
/*   Updated: 2023/10/31 19:22:19 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	env(t_cmd *cmd)
{
	if (!cmd->arg[1])
		print_env(cmd->data->env);
	else if (cmd->arg[1][0] == '-')
	{
		if (cmd->arg[1][1])
			printf("env: %c%c: Invalid option\n", cmd->arg[1][0], cmd->arg[1][1]);
	} 
	else
	{
		if (!access(cmd->arg[1], F_OK))
			printf("env: %s: Permission denied\n", cmd->arg[1]);
		else
			printf("env: %s: No such file or directory\n", cmd->arg[1]);
	}
}