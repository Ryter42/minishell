/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:43:37 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/21 23:32:35 by elias            ###   ########.fr       */
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
			ft_close(&cmd->data->fd_tmp);
		// dprintf(2, "fd in == %d\n\n", fd);		
	}
	else if (cmd->heredoc)
	{
		// dprintf(2, "heredoc = %d\n\n", cmd->heredoc);
		fd = open(".heredoc_tmp", O_RDONLY);
		if (index)
			ft_close(&cmd->data->fd_tmp);
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
		// ft_close(&cmd->data->fd_tmp);
		return (0);
	}
	if (fd == -1)
	{
		ft_close(&cmd->data->fd[0]);
		ft_close(&cmd->data->fd[1]);
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
	
	ft_close(&cmd->data->fd[0]); 
	fd = open_infile(cmd, index);
	// cmd->data->fd_in = fd;
	// if (!index)
	// 	ft_close(&cmd->data->fd_tmp);
	// dprintf(2, "2-fd in == %d\n\n", fd);
	if (fd)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("redir in");
			ft_close(&fd);
			free_all(cmd);
			exit (EXIT_FAILURE);
		}
		ft_close(&fd);
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
		ft_close(&cmd->data->fd[1]);
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
		ft_close(&cmd->data->fd[1]);
		return (0);
	}
	if (fd == -1)
	{
		ft_close(&cmd->data->fd[0]);
		ft_close(&cmd->data->fd[1]);
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
		// ft_close(&cmd->data->fd[0]);
		//backup_out = dup(STDOUT_FILENA)
		if (dup2(fd, STDOUT_FILENO) == - 1)
		{
			perror("redir out");
			ft_close(&fd);
			free_all(cmd);
			exit (EXIT_FAILURE);
		}
		ft_close(&fd);
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

int	check_directory(char *str)
{
	int	fd;

	fd = open(str, __O_DIRECTORY);
	if (fd > 0)
	{
		// printf("%s: is a directory\n", str);
		ft_close(&fd);
		return (1);
	}
	else
		return (0);
}

void	print_error(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	// ft_putstr_fd(": No such file or directory\n", 2);
	// else
		// ft_putstr_fd(": command not found\n", 2);
}

int	is_return(char *cmd)
{
	// int i = 0;
	// while (cmd[i])
	// 	write(1, &cmd[i++], 1);
	if (cmd[0] == '.' && cmd[1] == '.' && !cmd[2])
		return (1);
	else
		return (0);
}

int	cmd_verif(t_cmd *cmd)
{
	if (access(cmd->cmd, F_OK) == -1 || is_return(cmd->cmd))
	{
		if (is_there_slash(cmd->cmd))
			print_error(cmd->cmd, ": No such file or directory\n");
		else
			print_error(cmd->cmd, ": command not found\n");
		return (0);
	}
	// else if (is_return(cmd->arg[0]))
	// {
	// 	print_error(cmd->arg[0], ": command not found\n");
	// 	return (0);
	// }
	
	// else if (access(cmd->cmd, X_OK))
	// {
	// 	perror(cmd->arg[0]);
	// 	return (0);
	// }
	else if (check_directory(cmd->arg[0]))
	{
		print_error(cmd->cmd, ": is a directory\n");
		return (0);
	}
	else
		return (1);
}

void	exec(t_cmd *cmd, int index)
{
	// mettre waitpid au bon endroit
	
	// print_cmd(cmd);
	// printf("address de data dans exec = %p\n", cmd->data);
	// printf("cmd->next = %p\n", cmd->next);

	// signal(SIGQUIT, signal_ctrl_backslash);
	// free(cmd->data->pid);
	// if (cmd->limiter && (is_fork_bultin(cmd, index) || !cmd->bultin || !cmd->cmd))
	// 	ft_heredoc(cmd);
	// (void)index;
	// print_cmd(cmd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c_child);
	dup_infile(cmd, index);
	dup_outfile(cmd);
	// ft_redir(cmd, index);
	if (!cmd->cmd)
	{
		dprintf(2, "free all\n");
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
		if (!cmd_verif(cmd))
			ft_exit(cmd, 1);
		else if (execve(cmd->cmd, cmd->arg, cmd->data->env) == -1)
		{
			
			perror(cmd->arg[0]);
			free_all(cmd);
			exit(127);
		}
	}
}
