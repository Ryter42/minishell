/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:21:10 by elias             #+#    #+#             */
/*   Updated: 2023/11/15 23:08:55 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	free_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		ft_free(tab[i]);
// 		i++;
// 	}
// }

void	ft_exit(t_cmd *cmd)
{
	// ft_free(cmd->data->pid);
	free_all(cmd);
	exit(1);
}