/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:14:00 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/16 21:00:22 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_next_line(int fd, int c)
{
	char	*line;
	char	*buf;

	if (c != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
	}
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	line = nextline(fd, c, buf);
	return (line);
}

char	*nextline(int fd, int c, char *buf)
{
	static char	*stash;
	char		*line;
	ssize_t		readed;

	if (c == 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
			return (free(buf), NULL);
		buf[readed] = '\0';
		stash = ft_strjoin_gnl(stash, buf);
		if (backslash(buf) == 1)
			break ;
	}
	if (readed <= 0 && stash[0] == 0)
		return (free(buf), free(stash), stash = NULL, NULL);
	line = inistash(stash);
	stash = freestash(stash);
	return (free(buf), line);
}

char	*freestash(char *stash)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (ft_strlen_gnl(stash) - i + 1));
	if (!str)
		return (NULL);
	while (stash[i])
	{
		str[j] = stash[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(stash);
	return (str);
}

char	*inistash(char *stash)
{
	int		i;
	char	*line;

	if (!stash)
		return (NULL);
	line = malloc(sizeof(char) * (sizeline(stash) + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
