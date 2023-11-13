/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:26:30 by elias             #+#    #+#             */
/*   Updated: 2023/11/01 00:20:08 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cpy_env_without(char **env, int indice)
{
	char **res;
	int	i;
	int	j;

	j = 0;
	i = 0;
	res = malloc(sizeof(char *) * (strllen(env)));
	while (env[j])
	{
		if (j == indice)
			j++;
		else
		{
			res[i] = env[j];
			i++;
			j++;
		}
	}
	res[i] = 0;
	free(env);
	return (res);
}

int	find_unset_indice(char **env, char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], arg, ft_strlen(arg)) && env[i][ft_strlen(arg)] == '=')
			break ;
		i++;
	}
	if (env[i])
		return (i);
	else
		return (-1);
}

void	unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	dprintf(2, "unset\n");
	print_cmd(cmd);
	if (!cmd->arg[1])
		return ;
	if (cmd->arg[1][0] == '-' && cmd->arg[1][1])
	{
		printf("bash: export: %c%c: invalid option", cmd->arg[1][0], cmd->arg[1][1]);
		return ;
	}
	while (cmd->arg[i])
	{
		if (find_unset_indice(cmd->data->env, cmd->arg[i]) >= 0)
			cmd->data->env = cpy_env_without(cmd->data->env, find_unset_indice(cmd->data->env, cmd->arg[i]));
		i++;
	}
}