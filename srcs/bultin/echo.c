/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:23:18 by elias             #+#    #+#             */
/*   Updated: 2023/10/29 19:37:51 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	newline(char **arg)
{
	int	i;

	i = 0;
	while (arg[i + 1][0] == '-' && arg[i + 1][1] == 'n' && !arg[i + 1][2])
		i++;
	return (i);
}

void	echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	nl = newline(cmd->arg);
	printf ("nl = %d\n", nl);
	i = 1 + nl;
	while (cmd->arg[i])
	{
		// dprintf(2, "%s", cmd->arg[i]);
		printf("%s", cmd->arg[i]);
		// ft_printf("%s", cmd->arg[i]);
		if (cmd->arg[i + 1])
			printf(" ");
		// printf("test");
		// write(1, " ", 1);
		i++;
	}
	if (!nl)
		printf("\n");
		// write (1, "\n", 1);
}
