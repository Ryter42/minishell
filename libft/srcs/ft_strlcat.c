/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:52:02 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/16 17:59:09 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		k;

	k = ft_strlen(dst);
	i = k;
	if (size == 0)
		return (ft_strlen(src));
	if (size < k)
		return (size + ft_strlen(src));
	j = 0;
	if (size > i)
	{
		while (src[j] && size - i > 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
	while (src[j] != '\0')
		j++;
	return (k + j);
}
