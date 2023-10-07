/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:15:21 by emoreau           #+#    #+#             */
/*   Updated: 2023/09/25 13:03:00 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd, int c);
char	*nextline(int fd, int c, char *buf);
char	*inistash(char *stash);
int		backslash(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strlen_gnl(const char *str);
int		sizeline(char *str);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
char	*freestash(char *stash);

#endif