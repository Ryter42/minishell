/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:43:37 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/21 12:33:46 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_infile(t_cmd *cmd,int index)
{
	int	fd;

	// dprintf(2, "---dans infile----\n		cmd = %s	infile = %s	index = %d\n", cmd->cmd, cmd->infile,index);
	if (cmd->infile)
	{
		// dprintf(2, "infile = %s\n\n", cmd->infile);
		fd = open(cmd->infile, O_RDONLY);
		if (index)
			close(cmd->data->fd_tmp);
		// dprintf(2, "fd in == %d\n\n", fd);		
	}
	else if (cmd->heredoc)
	{
		// dprintf(2, "heredoc = %d\n\n", cmd->heredoc);
		fd = open(".heredoc_tmp", O_RDONLY);
		if (index)
			close(cmd->data->fd_tmp);
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
		// dprintf(2, "fd_tmp == %d\n", cmd->data->fd_tmp );
		// close(cmd->data->fd_tmp);
		return (0);
	}
	if (fd == -1)
	{
		close(cmd->data->fd[0]);
		close(cmd->data->fd[1]);
		printf("%s: %s: No such file or directory\n",rm_path(cmd->cmd), cmd->infile);
		// perror(cmd->infile);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	return (fd);
}


void	dup_infile(t_cmd *cmd, int index)
{
	int	fd;
	
	close(cmd->data->fd[0]); 
	fd = open_infile(cmd, index);
	// cmd->data->fd_in = fd;
	// if (!index)
	// 	close(cmd->data->fd_tmp);
	// dprintf(2, "2-fd in == %d\n\n", fd);
	if (fd)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("redir in");
			close(fd);
			free_all(cmd);
			exit (EXIT_FAILURE);
		}
		close(fd);
	}
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;

	if (cmd->outfile)
	{
		if (cmd->add_out)
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			// dprintf(2, "fd out == %d\n\n", fd);
		}
		else
		{
			// dprintf(2, "outfile == %s\n\n", cmd->outfile);
			fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			// fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			// dprintf(2, "fd out == %d\n\n", fd);
			// fd = open("elias", O_WRONLY | O_TRUNC | O_CREAT, 0644);
			// dprintf(2, "fd out == %d\n\n", fd);
		}
		close(cmd->data->fd[1]);
	}
	else if (cmd->next)
	{
		// dprintf(2, "cmd->next =  %p\n\n", cmd->next);
		// printf("fd = %d\n", cmd->data->fd[1]);
		fd = cmd->data->fd[1];
		// dprintf(2, "fd out == %d\n\n", fd);
	}
	else
	{
		// dprintf(2, "rien_out\n\n");
		close(cmd->data->fd[1]);
		return (0);
	}
	if (fd == -1)
	{
		close(cmd->data->fd[0]);
		close(cmd->data->fd[1]);
		perror(cmd->outfile);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	dup_outfile(t_cmd *cmd)
{
	int	fd;
	
	fd = open_outfile(cmd);
	// cmd->data->fd_out = fd;
	// dprintf(2, "cmd == %s 2-fd out == %d\n\n",cmd->cmd, fd);
	// dprintf(2, "2-fd out == %d\n\n", fd);
	if (fd)
	{
		// dprintf(2, "fd = %d\n", fd);
		// close(cmd->data->fd[0]);
		//backup_out = dup(STDOUT_FILENA)
		if (dup2(fd, STDOUT_FILENO) == - 1)
		{
			perror("redir out");
			close(fd);
			free_all(cmd);
			exit (EXIT_FAILURE);
		}
		close(fd);
	}
	// else
	// 	dprintf(2, "fd = 0\n");
}

void	printab(char **tab, char *var)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s ", var);
		printf("%d = %s	", (i + 1), tab[i]);
		i++;
	}
	printf("\n");
}

void	print_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		printf("cmd = %s\n", cmd->cmd);
	if (cmd->infile)
		printf("infile = %s\n", cmd->infile);
	if (cmd->heredoc)
		printf("heredoc = %d\n", cmd->heredoc);
	if (cmd->limiter)
		printab(cmd->limiter, "limiter");
	if (cmd->arg)
		printab(cmd->arg, "arg");
	if (cmd->outfile)
		printf("outfile = %s\n", cmd->outfile);
	if (cmd->add_out)
		printf("add = %d\n", cmd->add_out);
}

char	*rm_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	i--;
	while (i > 0 && path[i] != '/')
		i--;
	// dprintf(2, "----------------i = %d\n", i);
	if (i == 0)
		return (path);
	else
		return (path + i + 1);
}

void	exec(t_cmd *cmd, int index)
{
	// mettre waitpid au bon endroit
	
	// print_cmd(cmd);
	// printf("address de data dans exec = %p\n", cmd->data);
	// printf("cmd->next = %p\n", cmd->next);

	// signal(SIGQUIT, signal_ctrl_backslash);
	// free(cmd->data->pid);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ctrl_c_exec);
	signal(SIGQUIT, SIG_IGN);
	// if (cmd->limiter && (is_fork_bultin(cmd, index) || !cmd->bultin || !cmd->cmd))
	// 	ft_heredoc(cmd);
	// (void)index;
	// print_cmd(cmd);
	dup_infile(cmd, index);
	dup_outfile(cmd);
	// ft_redir(cmd, index);
	if (!cmd->cmd)
	{
		// dprintf(2, "free all\n");
		free_all(cmd);
		exit(EXIT_SUCCESS);
	}
	// printf("bultin = %d\n", cmd->bultin);
	if (cmd->bultin)
	{
		exec_fork_bultin(cmd, index);
		free_all(cmd);
		exit(1);
	}
	
	else
	{
		if (execve(cmd->cmd, cmd->arg, cmd->data->env) == -1)
		{
			perror(rm_path(cmd->cmd));
			free_all(cmd);
			exit(EXIT_FAILURE);
		}
	}
}
