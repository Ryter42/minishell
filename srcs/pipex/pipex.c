/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:51:39 by elias             #+#    #+#             */
/*   Updated: 2023/10/24 21:18:25 by emoreau          ###   ########.fr       */
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


void	loopfork(t_cmd *cmd)
{
	// pid_t	*pid;
	// int		fd[2];
	int		fd_tmp;
	int		nb_loop;

	nb_loop = 0;
	cmd->data->nb_cmd = ft_nb_cmd(cmd);
	cmd->data->pid = malloc(sizeof(pid_t) * (cmd->data->nb_cmd));
	while (cmd)
	{
		if (pipe(cmd->data->fd) < 0)
			return ;
		cmd->data->pid[nb_loop] = fork();
		if (cmd->data->pid[nb_loop] < 0)
			return ;
		if (cmd->data->pid[nb_loop] == 0)
			exec(cmd, nb_loop);
		if (cmd->data->fd[1])
			close(cmd->data->fd[1]);
		if (fd_tmp)
			close(fd_tmp);
		fd_tmp = cmd->data->fd[0];
		waitpid(cmd->data->pid[nb_loop], NULL, 0);
		nb_loop++;
		cmd = cmd->next;
	}
	close(fd_tmp);
}

void	ft_wait(t_data *data)
{
	while (data->nb_cmd-- >= 0)
	{
		waitpid(data->pid[data->nb_cmd], NULL, 0);
	}
	free(data->pid);
}

int	execution(t_cmd *cmd)
{
	// t_data	*data;
// 
	// if (ac < 5)
		// return (ft_printf("Error arg\n"), 1);
	// data = init(data);
	loopfork(cmd);
	ft_free(cmd);
	unlink(".heredoc_tmp");
	return (0);
}
