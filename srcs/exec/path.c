/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:41:05 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/17 15:27:17 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pathenv(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i])
		return (env[i] + 5);
	else
		return (NULL);
}

int	is_there_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**addslash(char **env)
{
	char	**path;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(pathenv(env), ":");
	if (!tmp)
		return (NULL);
	path = malloc(sizeof(char *) * (strllen(tmp) + 1));
	if (!path)
		return (NULL);
	while (tmp[i])
	{
		path[i] = ft_strjoin(tmp[i], "/");
		i++;
	}
	path[i] = NULL;
	free_tab(tmp);
	return (path);
}

int	findpath(t_data *data, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	// printf("data = %p\n", data);
	// printf("path = %p\n", data->path);
	if (data->path)
	{
		while (data->path[i])
		{
			tmp = ft_strjoin(data->path[i], cmd);
			if (access(tmp, F_OK) == 0)
				return (free(tmp), i);
			free(tmp);
			i++;
		}
	}
	printf("%s : command not found\n", cmd);
	// close(data->fd[1]);
	// close(data->fd[0]);
	// close(data->fd_tmp);
	// ft_ft_free(data);
	// exit(EXIT_FAILURE);
	return (-1);
}
