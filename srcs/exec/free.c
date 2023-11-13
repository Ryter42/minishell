/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:38:55 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/31 17:26:00 by elias            ###   ########.fr       */
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

void	free_data(t_data *data)
{
	if (data->env)
		free_tab(data->env);
	if (data->path)
		free_tab(data->path);
	if (data->pid)
		free(data->pid);
	if (data->str)
		free(data->str);
}

// void	free_cmd(t_cmd *cmd)
// {
// 	if (cmd->cmd)
// 		free(cmd->cmd);
// 	if (cmd->infile)
// 		free(cmd->infile);
// 	// if (cmd->heredoc)
// 	// 	free("heredoc = %d\n", cmd->heredoc);
// 	if (cmd->limiter)
// 		free_tab(cmd->limiter);
// 	if (cmd->arg)
// 		free_tab(cmd->arg);
// 	if (cmd->outfile)
// 		free(cmd->outfile);
// }

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		// if (cmd->arg)
		// 	free_tab(cmd->arg);
		// if (cmd->cmd)
		// 	free(cmd->cmd);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->limiter)
			free_tab(cmd->limiter);
		if (cmd->outfile)
			free(cmd->outfile);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_all(t_cmd *cmd)
{
	free_data(cmd->data);
	free_cmd(cmd);
}