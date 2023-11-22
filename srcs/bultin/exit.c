/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:21:10 by elias             #+#    #+#             */
/*   Updated: 2023/11/22 20:01:57 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	free_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// }

void	print_exit_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	// ft_putstr_fd(": numeric argument required\n");
}

int	only_num(char *str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}



void	exit_ft(t_cmd *cmd,int status)
{
	// free(cmd->data->pid);
	free_all(cmd);
	exit(status);
}

void	ft_exit(t_cmd *cmd)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd->arg[1])
	{
			
		if (!only_num(cmd->arg[1]))
		{
			print_exit_error(cmd->arg[1], ": numeric argument required\n");
			exit_ft(cmd, 2);
		}
		if (strllen(cmd->arg) > 2)
		{
			status = 1;
			ft_putstr_fd("minishell: exit: too many arguments\n", 2); // msg erreur 1
		}
		else
			exit_ft(cmd, atoi(cmd->arg[1]));
	}
	else
		exit_ft(cmd, 0);
		
}