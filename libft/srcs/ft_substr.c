/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:59:35 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/26 16:27:58 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*des;

	i = 0;
	if (start > (size_t)ft_strlen(s) || len == 0)
	{
		des = malloc(sizeof(char));
		*des = 0;
	}
	else if (len > (size_t)ft_strlen(&s[start]))
		des = malloc(sizeof(char) * ft_strlen(&s[start]) + 1);
	else
		des = malloc(sizeof(char) * len + 1);
	if (!des)
		return (NULL);
	while ((int) start < ft_strlen(s) && s[start] && i < len)
	{
		des[i] = s[start];
		i++;
		start++;
	}
	des[i] = 0;
	return (des);
}
