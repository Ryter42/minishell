/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:43:37 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/24 23:30:06 by emoreau          ###   ########.fr       */
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
	{
		// dprintf(2, "infile = %s\n\n", cmd->infile);
		fd = open(cmd->infile, O_RDONLY);
		// dprintf(2, "fd in == %d\n\n", fd);		
	}
	else if (cmd->heredoc)
	{
		// dprintf(2, "heredoc = %d\n\n", cmd->heredoc);
		fd = open(".heredoc_tmp", O_RDONLY);
		// dprintf(2, "fd in == %d\n\n", fd);		
	}
	else if (index)
	{
		// dprintf(2, "pipe numero %d\n\n", index);
		fd = cmd->data->fd_tmp;
		// dprintf(2, "fd in == %d\n\n", fd);		
	}
	else
	{
		// dprintf(2, "rien_in\n\n");
		return (0);
	}
	if (fd == -1)
	{
		close(cmd->data->fd[0]);
		close(cmd->data->fd[1]);
		perror(cmd->infile);
		// ft_free(cmd);
		exit(EXIT_FAILURE);
	}
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
		else
		{
			// dprintf(2, "dupin de %d fait \n\n", fd);
		}
	}
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;

	if (cmd->outfile)
	{
		if (cmd->add_out)
		{
			fd = open(cmd->outfile, O_RDWR | O_CREAT, 0644); // apend
			// dprintf(2, "fd out == %d\n\n", fd);		
		}
		else
		{
			// dprintf(2, "outfile =  %s\n\n", cmd->outfile);
			fd = open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
			// dprintf(2, "fd out == %d\n\n", fd);		
		}
	}
	else if (cmd->next)
	{
		// dprintf(2, "cmd->next =  %p\n\n", cmd->next);
		fd = cmd->data->fd[1];
		// dprintf(2, "fd out == %d\n\n", fd);		
	}
	else
	{
		// dprintf(2, "rien_out\n\n");
		return (0);
	}
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
		dprintf(2, "fd = %d\n", fd);
		close(cmd->data->fd[0]);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("redir out");
			exit (EXIT_FAILURE);
		}
		close(fd);
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
	dup_infile(cmd, index);
	dup_outfile(cmd);
	if (execve(cmd->cmd, cmd->arg, cmd->data->env) == -1)
	{
		perror(cmd->cmd);
		exit(EXIT_FAILURE);
	}
}
