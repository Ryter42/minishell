/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:18:29 by elias             #+#    #+#             */
/*   Updated: 2023/11/18 23:29:34 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	sigint_handler(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(2, "\n", 1);
// 		// rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	set_signal_action(void)
// {
// 	struct sigaction	act;

// 	act.sa_handler = &sigint_handler;
//  	act.sa_sigaction = NULL;
//     act.sa_mask = 0;
//     act.sa_flags = 0;
// 	sigaction(SIGINT, &act, NULL);
// }

// struct sigaction	*struc_signal_controle_c(void)
// {
// 	struct sigaction	*act;

// 	act = malloc(sizeof(act));
// 	if (!act)
// 		return (NULL);
// 	act->sa_handler = &sigint_handler;
//  	act->sa_sigaction = NULL;
//     act->sa_mask = 0;
//     act->sa_flags = 0;
// 	return (act);
// }



// void	signal_ctrl_c_here_doc(int signo)
// {
// 	t_here_doc	*s;

// 	(void)signo;
// 	if (g_in_here_doc == 1)
// 	{
// 		s = starthd();
// 		g_in_here_doc = 130;
// 		close(s->fd);
// 		free(s->limiter);
// 		free(s->line);
// 		write(2, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		exit(130);
// 	}
// }

// void	signal_ctrl_c_in_child(int signo)
// {
// 	(void)signo;
// 	ft_putstr_fd("\n", 2);
// 	exit(0);
// }

// void	signal_ctrl_slash(int signo)
// {
// 	(void)signo;
// }

void	signal_ctrl_c(int signo)
{
	(void)signo;
	// if (g_in_here_doc != 1)
	// {
		// g_in_here_doc = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	// }
}

void	ctrl_c_hd(int signo)
{
	
	t_cmd *tmp;

	(void)signo;
	// status[1] = 1;
	tmp = give_adress();
	// printf("fd = %d\n", tmp->next->fd_heredoc);
	if (tmp->next->fd_heredoc > 1)
	{
		close(tmp->next->fd_heredoc);
		tmp->next->fd_heredoc = -1;
	}
	// dprintf(2, "appelle de free ctrl c\n");
	free_all(tmp->next);// faire une double list chainee pour pouvoir free les mailon precedent
	exit (130);
	// free_lst(cmd);
}

void	ctrl_c_exec(int signo)
{
	
	t_cmd *tmp;

	(void)signo;
	// status[1] = 1;
	tmp = give_adress();
	// printf("fd = %d\n", tmp->next->fd_heredoc);
	// close(tmp->next->fd_heredoc);
	// dprintf(2, "appelle de free ctrl c\n");
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	// write(2, "\n", 1);
	free_all(tmp->next);
	exit (130);
	// free_lst(cmd);
}

void	signal_ctrl_backslash(int signo)
{
	(void)signo;
}

// void	ctrl_d(int signo)
// {
// 	(void)signo;

// }