/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:23:18 by elias             #+#    #+#             */
/*   Updated: 2023/11/13 21:43:16 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	newline(char **arg)
{
	if (!arg[1])
		return (0);
	if (arg[1][0] == '-' && arg[1][1] == 'n' && !arg[1][2])
		return (1);
	else
		return (0);
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
