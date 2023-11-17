/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:04:26 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/17 22:57:53 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	is_heredoc(char *str)
// {
// 	if (ft_strncmp("here_doc", str, 9) == 0)
// 		return (1);
// 	else
// 		return (0);
// }

// void clearInputBuffer()
// {
//     int c;
//     while ((c = getchar()) != '\n' && c != EOF);
// }

void	fork_heredoc(t_cmd *cmd)
{
	pid_t pid;

	// signal(SIGINT, SIG_IGN);
	// status[1] = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, ctrl_c_hd);
		signal(SIGQUIT, SIG_IGN);
		ft_heredoc(cmd);
		free_all(cmd);
		// printf("no exit\n");

		exit(1);
	}
	// printf("data = %p\n", cmd->data);
	waitpid(pid, &cmd->data->status, 0);
	// printf("exit\n");
	cmd->data->status = WEXITSTATUS(cmd->data->status);
	// printf("status = %d\n", cmd->data->status);
	// status[1] = 0;
	// dprintf(1, "status = %d\n", status[1]);
}

void	ft_heredoc(t_cmd *cmd)
{
	int	i;
	// pid_t pid;

	// pid = fork();

	i = 0;
	// if (pid == 0)
	// {

	while (cmd->limiter[i])
	{
		heredoc(cmd, i);
		i++;
	}
	// printf("no exit\n");
	// }
	// else
	// 	waitpid(pid, status, 0);
}

// void	heredoc(t_cmd *cmd, int i)
// {
// 	char	*str;

// 	// write(1, "heredoc>", 8);
// 	cmd->fd_heredoc = ft_open_heredoc();
// 	status[1] = 1;
// 	str = readline("heredoc> ");
// 	// if (!str)
// 	while (str && (ft_strncmp(str, cmd->limiter[i], ft_strlen(cmd->limiter[i]))
// 			|| (ft_strlen(cmd->limiter[i]) != ft_strlen(str))))
// 	{
// 		// write(1, "heredoc>", 8);
// 		ft_putstr_fd(str, cmd->fd_heredoc);
// 		// free(str);
// 		str = readline("heredoc> ");
// 		if (!str)
// 			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
// 					cmd->limiter[i]);
// 		// cmd->hd_last_line = str;
// 	}
// 	// get_next_line(0, 0);
// 	// free(str);
// 	// cmd->hd_last_line = NULL;
// 	close(cmd->fd_heredoc);
// 	status[1] = 0;
// }

void	heredoc(t_cmd *cmd, int i)
{
	char	*str;

	// write(1, "heredoc>", 8);
	cmd->fd_heredoc = ft_open_heredoc();
	// str = readline("heredoc> ");
	// if (!str)
	while (1)
	{
		// write(1, "heredoc>", 8);
		str = readline("heredoc> ");
		if (!str || (!ft_strncmp(str, cmd->limiter[i], ft_strlen(cmd->limiter[i]))
			&& (ft_strlen(cmd->limiter[i]) == ft_strlen(str))))
		{
			if (!str)
				printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
					cmd->limiter[i]);
			break ;
		}
		ft_putstr_fd(str, cmd->fd_heredoc);
		ft_putstr_fd("\n", cmd->fd_heredoc);

		// free(str);
		// cmd->hd_last_line = str;
	}
	// get_next_line(0, 0);
	// free(str);
	// cmd->hd_last_line = NULL;
	// printf("no exit\n");
	close(cmd->fd_heredoc);
	// status[1] = 0;
}

// int	ft_open(t_data *data)
// {
// 	int	fd;

// 	if (data->heredoc == 1)
// 		fd = open(".heredoc_tmp", O_RDWR | O_CREAT, 0644);
// 	else
// 		fd = open(data->av[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		close(data->fd[0]);
// 		close(data->fd[1]);
// 		perror(data->av[1]);
// 		ft_ft_free(data);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (fd);
// }

int	ft_open_heredoc(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		unlink(".here_doc_tmp");
		fd = open(".heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("here_doc");
			// ft_ft_free(data);
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}
