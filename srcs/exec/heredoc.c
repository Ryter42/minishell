/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:04:26 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/27 04:06:37 by elias            ###   ########.fr       */
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

void	ft_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->limiter[i])
	{
		heredoc(cmd->limiter[i], ft_open_heredoc());
		i++;
	}
}

void	heredoc(char *limiter, int fd)
{
	char	*str;

	write(1, "heredoc>", 1);
	str = get_next_line(0, 1);
	while (str && ((ft_strncmp(str, limiter, ft_strlen(limiter)))
			|| (ft_strlen(limiter) != ft_strlen(str) - 1)))
	{
		write(1, "heredoc>", 1);
		ft_putstr_fd(str, fd);
		free(str);
		str = get_next_line(0, 1);
	}
	get_next_line(0, 0);
	free(str);
	close(fd);
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
// 		ft_free(data);
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
			// ft_free(data);
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}
