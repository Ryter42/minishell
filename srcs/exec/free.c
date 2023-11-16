/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:38:55 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/16 20:37:11 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printab(char **tab, char *var);

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	// if (!tab || tab == NULL)
	// 	return ;
	while (tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

void	free_data(t_data *data)
{
	// data->pid = NULL;
	// ft_free(data->pid);
	if (data->env)
		free_tab(data->env);
	if (data->path)
		free_tab(data->path);
	// if (data->pid)
	// 	ft_free(data->pid);
	if (data->str)
		ft_free(data->str);
	ft_free(data);
}

// void	free_cmd(t_cmd *cmd)
// {
// 	if (cmd->cmd)
// 		ft_free(cmd->cmd);
// 	if (cmd->infile)
// 		ft_free(cmd->infile);
// 	// if (cmd->heredoc)
// 	// 	ft_free("heredoc = %d\n", cmd->heredoc);
// 	if (cmd->limiter)
// 		free_tab(cmd->limiter);
// 	if (cmd->arg)
// 		free_tab(cmd->arg);
// 	if (cmd->outfile)
// 		ft_free(cmd->outfile);
// }

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd->pid)
		ft_free(cmd->pid);
	while (cmd)
	{
		// print_cmd(cmd);
		if (cmd->arg)
			free_tab(cmd->arg);
		if (cmd->infile)
			ft_free(cmd->infile);
		if (cmd->limiter)
			free_tab(cmd->limiter);
		if (cmd->outfile)
	|		ft_free(cmd->outfile);
		// if (cmd->hd_last_line)
		// {
		// 	ft_free(cmd->hd_last_line);
		// 	cmd->hd_last_line = NULL;	
		// }
		tmp = cmd;
		cmd = cmd->next;
		ft_free(tmp);
	}
	// if (str)
	// 	ft_free(str);
	// ft_free(free_struc);
}

void	free_all(t_cmd *cmd)
{
	// if (free_struc)
	// {
		if (cmd)
		{
			if (cmd->data)
				free_data(cmd->data);
			free_cmd(cmd);
		}
	// }
}

// void	ft_free(void *var)
// {
// 	if (var)
// 	{
// 		free(var);
// 		var = NULL;
// 	}
// }

// il reste la derniere ligne du heredoc qui veut pas se free quand on controle c
// ne pas oublier de verifier pour quand il y a plusieure here_doc
// et quand il y a plusieurs infile et outfile que tout soit bien free plus ensuite les valeur retours
// ls | unset
