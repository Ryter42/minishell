/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:38:55 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/21 15:34:10 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	printab(char **tab, char *var);

void	ft_close(int *fd)
{
	if (*fd > -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_int(int **tab)
{
	if (*tab)
	{
		free(*tab);
		*tab = NULL;
	}
}

void	free_array(char ***tab)
{
	if (*tab)
	{
		free(*tab);
		*tab = NULL;
	}
}

void	free_struc(t_cmd **cmd)
{
	if (*cmd)
	{
		free(*cmd);
		*cmd = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	// if (!tab || tab == NULL)
	// 	return ;
	while (tab[i])
	{
		free_str(&tab[i]);
		i++;
	}
	free_array(&tab);
}

void	free_data(t_data *data)
{
	// data->pid = NULL;
	// free(data->pid);
	if (data->env)
		free_tab(data->env);
	if (data->path)
		free_tab(data->path);
	// if (data->pid)
	// 	free(data->pid);
	if (data->str)
		free_str(&data->str);
	free(data);
}

// void	free_lst(t_cmd *cmd)
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

// void	free_cmd(t_cmd *cmd)
// {
// 	t_cmd	*tmp;

// 	if (cmd->pid)
// 		free_int(&cmd->pid);
// 	while (cmd)
// 	{
// 		// print_cmd(cmd);
// 		if (cmd->arg)
// 		{
// 			// dprintf(2, "free arg\n");
// 			free_tab(cmd->arg);
// 		}
// 		if (cmd->infile && (*cmd->infile))
// 		{
// 			// dprintf(2, "free infile\n");
// 			free(cmd->infile);
// 			cmd->infile = NULL;
// 		}
// 		if (cmd->limiter)
// 			free_tab(cmd->limiter);
// 		if (cmd->outfile)
// 		{
// 			// dprintf(2, "free outfile : %p\n", cmd->outfile);
// 			free_str(&cmd->outfile);
// 		}
// 		// if (cmd->hd_last_line)
// 		// {
// 		// 	free(cmd->hd_last_line);
// 		// 	cmd->hd_last_line = NULL;	
// 		// }
// 		tmp = cmd;
// 		cmd = cmd->next;
// 		free_struc(&tmp);
// 	}
// 	// if (str)
// 	// 	free(str);
// 	// free(free_struc);
// }

void	free_cmd(t_cmd *cmd)
{
	if (cmd->arg)
	{
		cmd->arg[0] = cmd->cmd;
		free_tab(cmd->arg);
	}
	if (cmd->limiter)
		free_tab(cmd->limiter);
	if (cmd->infile)
		free_str(&cmd->infile);
	if (cmd->outfile)
		free_str(&cmd->outfile);
}

void	free_prev_lst(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		free_cmd(cmd);
		tmp = cmd;
		cmd = cmd->prev;
		free_struc(&tmp);
	}
}

void	free_next_lst(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		free_cmd(cmd);
		tmp = cmd;
		cmd = cmd->next;
		free_struc(&tmp);
	}
}

void	free_lst(t_cmd *cmd)
{
	if (cmd)
	{
		// if (cmd->pid)
		// 	free_int(&cmd->pid);
		if (cmd->next)
			free_next_lst(cmd->next);
		if (cmd->prev)
			free_prev_lst(cmd->prev);
		free_cmd(cmd);
		free_struc(&cmd);
	}
		
}

void	free_all(t_cmd *cmd)
{
	// if (free_struc)
	// {
		if (cmd)
		{
			if (cmd->data)
				free_data(cmd->data);
			free_lst(cmd);
		}
	// }
}

// void	free(void *var)
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
