/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:23 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/18 17:15:33 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*des;
	char	*source;

	des = dest;
	source = (char *) src;
	i = 0;
	while (i < n)
	{
		des[i] = source[i];
		i++;
	}
	return (dest);
}
