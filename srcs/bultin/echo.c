/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:23:18 by elias             #+#    #+#             */
/*   Updated: 2023/11/21 13:13:50 by emoreau          ###   ########.fr       */
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
	i = 1 + nl;
	while (cmd->arg[i])
	{
		// dprintf(2, "%s", cmd->arg[i]);
		if (ft_print_str(cmd->arg[i]) < 0)
		{
			write(2, "echo: write error: No space left on device\n", 43);
			ft_exit(cmd);
		}
		// ft_ft_print_str("%s", cmd->arg[i]);
		if (cmd->arg[i + 1])
			ft_print_str(" ");
		// ft_print_str("test");
		// write(1, " ", 1);
		i++;
	}
	if (!nl)
		if (ft_print_str("\n"))
			write(2, "echo: write error: No space left on device\n", 43);
	// if (write(1, " ", 1) == -1)
	// 	write(2, "OK\n", 3);
		
		// write (1, "\n", 1);
}
