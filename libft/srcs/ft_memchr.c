/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:57:06 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/18 11:43:03 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*src;

	i = 0;
	src = (char *) s;
	while (i < n)
	{
		if (src[i] == ((char)c))
			return (src + i);
		i++;
	}
	return (0);
}
