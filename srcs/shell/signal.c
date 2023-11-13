/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:18:29 by elias             #+#    #+#             */
/*   Updated: 2023/11/01 19:18:50 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal_action(void)
{
	struct sigaction	act;

	act.sa_handler = &sigint_handler;
 	act.sa_sigaction = NULL;
    act.sa_mask = 0;
    act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
}

struct sigaction	*struc_signal_controle_c(void)
{
	struct sigaction	*act;

	act = malloc(sizeof(act));
	if (!act)
		return (NULL);
	act->sa_handler = &sigint_handler;
 	act->sa_sigaction = NULL;
    act->sa_mask = 0;
    act->sa_flags = 0;
	return (act);
}