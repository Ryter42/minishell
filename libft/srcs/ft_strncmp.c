/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:13:28 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/31 17:12:41 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	if (n == 0 || (!str1 && !str2))
		return (0);
	if (!str1)
		return(- *str2);
	if (!str2)
		return(*str1);
	while (str1[i] == str2[i] && i < n - 1 && (str1[i] && str2[i]))
		i++;
	return (str1[i] - str2[i]);
}
