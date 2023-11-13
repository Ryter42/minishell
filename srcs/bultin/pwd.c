/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:49:10 by elias             #+#    #+#             */
/*   Updated: 2023/10/30 23:21:18 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*find_pwd(char **env)
// {
// 	int	i;
// 	char *res;
// 	char *tmp;

// 	i = 0;
// 	tmp = find_var(env, "PWD", 3);
// 	res = malloc(sizeof(char) * ft_strlen(tmp) - 3);
// 	while (tmp[i + 3])
// 	{
// 		res[i] = tmp[i + 3];
// 		i++;
// 	}
// 	res[i] = 0;
// 	return (res);
// }

void	pwd(t_cmd *cmd)
{
	char	*pwd;
	if (cmd->arg[1] && cmd->arg[1][0] == '-' && cmd->arg[1][1])
		printf("pwd: %c%c: Invalid option\n", cmd->arg[1][0], cmd->arg[1][1]);
	else
	{
		pwd = find_var(cmd->data->env, "PWD", 3);
		printf("%s\n", pwd);
		free(pwd);
	}
}