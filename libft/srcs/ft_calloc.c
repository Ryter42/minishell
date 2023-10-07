/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:24:28 by emoreau           #+#    #+#             */
/*   Updated: 2022/12/28 19:11:56 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	s = malloc(nmemb * size);
	if (!s)
		return (NULL);
	ft_bzero(s, size * nmemb);
	return (s);
}
