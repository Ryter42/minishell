/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:02:20 by elias             #+#    #+#             */
/*   Updated: 2023/11/20 19:08:13 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_status(t_cmd *cmd)
{
	int	sig_status;

	if (WIFEXITED(cmd->data->status))
		cmd->data->status = WEXITSTATUS(cmd->data->status);
	if (WIFSIGNALED(cmd->data->status))
	{
		sig_status = WTERMSIG(cmd->data->status);
		ft_print_all_error_sig(sig_status);
		cmd->data->status = 128 + sig_status;
	}
}

void	ft_print_all_error_sig(int sig_status)
{
	ft_print_error_sig1(sig_status);
	ft_print_error_sig2(sig_status);
}

void	ft_print_stder(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_print_error_sig1(int sig_status)
{
	if (sig_status == 1)
		ft_print_stder("Hangup\n");
	else if (sig_status == 4)
		ft_print_stder("Illegal Instruction\n");
	else if (sig_status == 5)
		ft_print_stder("Trace/Breakpoint Trap\n");
	else if (sig_status == 6)
		ft_print_stder("Abort\n");
	else if (sig_status == 7)
		ft_print_stder("Emulation Trap\n");
	else if (sig_status == 8)
		ft_print_stder("Arithmetic Exception\n");
	else if (sig_status == 9)
		ft_print_stder("Killed\n");
	else if (sig_status == 10)
		ft_print_stder("Bus Error\n");
	else if (sig_status == 11)
		ft_print_stder("Segmentation Fault\n");
	else if (sig_status == 12)
		ft_print_stder("Bad System Call\n");
	else if (sig_status == 13)
		ft_print_stder("Broken Pipe\n");
	else if (sig_status == 14)
		ft_print_stder("Alarm Clock\n");
}

void	ft_print_error_sig2(int sig_status)
{
	if (sig_status == 15)
		ft_print_stder("Terminated\n");
	else if (sig_status == 16)
		ft_print_stder("User Signal 1\n");
	else if (sig_status == 17)
		ft_print_stder("User Signal 2\n");
	else if (sig_status == 23)
		ft_print_stder("Stopped (signal)\n");
	else if (sig_status == 24)
		ft_print_stder("Stopped (user)\n");
	else if (sig_status == 26)
		ft_print_stder("Stopped (tty input)\n");
	else if (sig_status == 27)
		ft_print_stder("Stopped (tty output)\n");
	else if (sig_status == 28)
		ft_print_stder("Virtual Timer Expired\n");
	else if (sig_status == 29)
		ft_print_stder("Profiling Timer Expired\n");
	else if (sig_status == 30)
		ft_print_stder("CPU time limit exceeded\n");
	else if (sig_status == 31)
		ft_print_stder("File size limit exceeded\n");
	else if (sig_status == 3)
		ft_print_stder("Quit (core dumped)\n");
}
