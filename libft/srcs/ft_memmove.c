/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:17:45 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/21 23:06:17 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*t;
	unsigned char	*s;

	if (src == dest || !n)
		return (dest);
	if (dest < src)
	{
		t = (unsigned char *)dest;
		s = (unsigned char *)src;
		while (n--)
			*t++ = *s++;
	}
	else
	{
		t = (unsigned char *)dest + (n - 1);
		s = (unsigned char *)src + (n - 1);
		while (n--)
			*t-- = *s--;
	}
	return (dest);
}
