/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:21:21 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/24 00:18:59 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	char	*res;

	res = (char *)s1;
	i = 0;
	if (*s2 == 0)
		return (res);
	while (*res && i < len)
	{
		if (ft_strncmp(res, s2, ft_strlen(s2)) == 0
			&& i + ft_strlen(s2) - 1 < len)
			return (res);
		res++;
		i++;
	}
	return (NULL);
}
