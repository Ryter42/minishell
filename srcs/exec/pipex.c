/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:51:39 by elias             #+#    #+#             */
/*   Updated: 2023/11/19 18:19:20 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_data_pipex	*init(int ac, char **av, char **env)
// {
// 	t_data	*data;

// 	data = malloc(sizeof(t_data));
// 	data->fd_tmp = 0;
// 	data->arg = NULL;
// 	data->cmd = NULL;
// 	data->path = addslash(env);
// 	data->av = av;
// 	data->env = env;
// 	data->ac = ac;
// 	data->heredoc = is_heredoc(av[1]);
// 	if (data->heredoc == 1)
// 	{
// 		data->limiteur = av[2];
// 		heredoc(data, ft_open_heredoc(data));
// 	}
// 	data->index = 2 + data->heredoc;
// 	return (data);
// }

int	ft_nb_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

void	backup(t_cmd *cmd)
{
	cmd->data->fd_out = dup(STDOUT_FILENO);
	if (cmd->data->fd_out == -1)
		perror("dup out");
	cmd->data->fd_in = dup(STDIN_FILENO);
	if (cmd->data->fd_in == -1)
		perror("dup in");
	// dup_infile(cmd, index);
	// dup_outfile(cmd);
}

void	loopfork(t_cmd *cmd)
{
	// pid_t	*pid;
	// int		fd[2];
	// int		fd_tmp;
	// int		nb_loop;
	t_cmd	*tmp;
	// t_cmd	*tmp2;

	// nb_loop = 0;
	// printf("cmd = %p\n", cmd);
	// printf("cmd->next = %p\n", cmd->next);
	// printf("cmd->data = %p\n", cmd->data);
	// tmp2 = cmd;
	// fd_tmp = 0;
	cmd->data->nb_cmd = ft_nb_cmd(cmd);
	cmd->pid = malloc(sizeof(pid_t) * (cmd->data->nb_cmd));
	cmd->data->nb_cmd = 0;
	
	// dprintf(2, " cmd numero %d\n", cmd->data->nb_cmd);
	// dprintf(2, "\n\ndebut de la commande fd_tmp = %d\n\n", cmd->data->fd_tmp);
	while (cmd && cmd->data->status != 130)
	{
		if (cmd->next)
			cmd->next->pid = cmd->pid;
		if (cmd->limiter)
			fork_heredoc(cmd);
		// printf("boucle\n");
		if (pipe(cmd->data->fd) < 0)
			return ;
		backup(cmd);
		cmd->pid[cmd->data->nb_cmd] = fork();
		if (cmd->pid[cmd->data->nb_cmd] < 0)
			return ;
		if (cmd->pid[cmd->data->nb_cmd] == 0)
		{
			if (cmd->data->status != 130)
				exec(cmd, cmd->data->nb_cmd);
			else
			{
				// free(cmd->pid);
				free_all(cmd);
				exit(130);
			}
		}
		if (cmd->bultin)
			waitpid(cmd->pid[cmd->data->nb_cmd], NULL, 0); // il faudrait essayer de trouver un e meileur solution	
		// exec_fork_bultin(cmd, cmd->data->nb_cmd);
		if (!cmd->next && !cmd->data->nb_cmd && is_env_bultin(cmd) == 1)
		{
			if (cmd->data->status != 130)
				exec_env_bultin(cmd, cmd->data->nb_cmd);
		}
		if (cmd->data->fd[1])
			close(cmd->data->fd[1]);
		if (cmd->data->nb_cmd && cmd->data->fd_tmp)
			close(cmd->data->fd_tmp);
		cmd->data->fd_tmp = cmd->data->fd[0];
		cmd->data->nb_cmd++;
		// nb_loop++;
		tmp = cmd;
		// fd_tmp = tmp->data->fd_tmp;
		cmd = cmd->next;
		// free_cmd(tmp);
		// free_struc(&cmd);
	}
	close(tmp->data->fd_tmp);
	// dprintf(2, "\n\nfin de la commande fd_tmp = %d\n\n", tmp->data->fd_tmp);
}

int	ft_wait(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->data->nb_cmd)
	{
		// dprintf(2, " wait numero %d\n", cmd->data->nb_cmd);
		waitpid(cmd->pid[i], &cmd->data->status, 0);
		i++;
	}
	// printf("status1 = %d\n", cmd->data->status);
	// free(cmd->pid);
	return (cmd->data->status);
}

void	reset_in_out(t_cmd *cmd)
{
	if (dup2(cmd->data->fd_out, STDOUT_FILENO) == - 1)
	{
		perror("reset redir out");
		exit (EXIT_FAILURE);
	}
	close(cmd->data->fd_out);
	if (dup2(cmd->data->fd_in, STDIN_FILENO) == -1)
	{
		perror("reset redir in");
		exit (EXIT_FAILURE);
	}
	close(cmd->data->fd_out);
	// ne fonctionne pas a tester avec la commande < Makefile echo
}

// void	reset_in_out(void)
// {
// 	if (dup2(1, STDOUT_FILENO) == - 1)
// 	{
// 		perror("redir out");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (dup2(0, STDIN_FILENO) == -1)
// 	{
// 		perror("redir in");
// 		exit (EXIT_FAILURE);
// 	}
// }



int	execution(t_cmd *cmd)
{
	int status;
	// t_data	*data;
// 
	// if (ac < 5)
		// return (ft_printf("Error arg\n"), 1);
	// data = init(data);
	// t_free *free_struc;

	// free_struc = malloc(sizeof(t_free));
	// global = cmd;
	// free_struc->str = NULL;
	// global = free_struc;
	loopfork(cmd);
	// cmd->data->status = ft_wait(cmd);
	status = ft_wait(cmd);
	printf("status = %d\n", status);
	reset_in_out(cmd);
	// dprintf(2, "appelle de free dans execution\n");
	free_lst(cmd);
	unlink(".heredoc_tmp");
	// printf("address de data dans execution = %p\n", cmd->data);
	return (status);
}

/*
valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.txt -s ./minishell
des que tu capte $ if (?) remplace par status

*/