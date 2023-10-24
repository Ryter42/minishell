/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:43:37 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/24 21:29:22 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	get_cmd(t_data *data)
// {
// 	data->arg = ft_split(data->av[data->index], ' ');
// 	if (is_there_slash(data->av[data->index]) == 0)
// 	{
// 		data->file = findpath(data->path, data->arg[0], data);
// 		data->cmd = ft_strjoin(data->path[data->file], data->arg[0]);
// 	}
// 	else
// 		data->cmd = ft_strdup(data->av[data->index]);
// }

// void	firstcmd(t_data *data)
// {
// 	int	fd;

// 	fd = ft_open(data);
// 	close(data->fd[0]);
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		perror("redir in");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 	{
// 		perror("redir out");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (execve(data->cmd, data->arg, data->env) == -1)
// 	{
// 		perror(data->cmd);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	midlecmd(t_data *data)
// {
// 	close(data->fd[0]);
// 	if (dup2(data->fd_tmp, STDIN_FILENO) == -1)
// 	{
// 		perror("redir in");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 	{
// 		perror("redir out");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (execve(data->cmd, data->arg, data->env) == -1)
// 	{
// 		perror("data->cmd");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	lastcmd(t_data *data)
// {
// 	int	fd;

// 	if (data->heredoc)
// 		fd = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		fd = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	close(data->fd[1]);
// 	if (dup2(data->fd_tmp, STDIN_FILENO) == -1)
// 	{
// 		perror("redir in");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("redir out");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (execve(data->cmd, data->arg, data->env) == -1)
// 	{
// 		perror(data->cmd);
// 		exit(EXIT_FAILURE);
// 	}
// }

int	open_infile(t_cmd *cmd,int index)
{
	int	fd;

	if (cmd->infile)
		fd = open(cmd->infile, O_RDONLY);
	else if (cmd->heredoc)
		fd = open(".heredoc_tmp", O_RDONLY);
	else if (index)
		fd = cmd->data->fd_tmp;
	if (fd == -1)
	{
		close(cmd->data->fd[0]);
		close(cmd->data->fd[1]);
		perror(cmd->infile);
		// ft_free(cmd);
		exit(EXIT_FAILURE);
	}
	else
		return (0);
	return (fd);
}


void	dup_infile(t_cmd *cmd, int index)
{
	int	fd;
	
	fd = open_infile(cmd, index);
	if (fd)
	{
		// fd = open_infile(cmd);
		close(cmd->data->fd[0]);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("redir in");
			exit (EXIT_FAILURE);
		}
	}
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;

	if (cmd->outfile)
	{
		if (cmd->add_out)
			fd = open(cmd->infile, O_RDWR | O_CREAT);
		else
			fd = open(cmd->infile, O_RDWR | O_CREAT | O_TRUNC);
	}
	else if (cmd->next)
		fd = cmd->data->fd[1];
	else
		return (0);
	if (fd == -1)
	{
		close(cmd->data->fd[0]);
		close(cmd->data->fd[1]);
		perror(cmd->outfile);
		// ft_free(cmd);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	dup_outfile(t_cmd *cmd)
{
	int	fd;
	
	fd = open_outfile(cmd);
	if (fd)
	{
		// fd = open_outfile(cmd);
		close(cmd->data->fd[0]);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("redir in");
			exit (EXIT_FAILURE);
		}
	}
}

void	exec(t_cmd *cmd, int index)
{
	(void)index;
	// get_cmd(data);
	// if (data->index == 2 + data->heredoc)
	// 	firstcmd(data);
	// else if (data->index <= data->ac - 3)
	// 	midlecmd(data);
	// else
	// 	lastcmd(data);
	// close(data->fd[0]);
	// if (dup2(data->fd_tmp, STDIN_FILENO) == -1)
	// {
	// 	perror("redir in");
	// 	exit (EXIT_FAILURE);
	// }
	// if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	// {
	// 	perror("redir out");
	// 	exit (EXIT_FAILURE);
	// }
	// dup_infile(cmd, index);
	// dup_outfile(cmd);
	if (execve(cmd->cmd, cmd->arg, cmd->data->env) == -1)
	{
		perror(cmd->cmd);
		exit(EXIT_FAILURE);
	}
}
