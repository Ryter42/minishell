/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:38:55 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/23 19:38:32 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free(t_data *data)
{
	ft_wait(data);
	// if (data->arg)
	// 	free_tab(data->arg);
	// if (data->cmd)
	// 	free(data->cmd);
	// if (data->path)
	// 	free_tab(data->path);
	// if (data)
	// 	free(data);
}
