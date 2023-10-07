/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:53:46 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/26 17:13:48 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	setverif(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;

	len = ft_strlen(s1);
	j = 0;
	i = 0;
	while (setverif(set, s1[i]) == 1 && s1[i])
		i++;
	while (setverif(set, s1[len - j - 1]) == 1 && i < len)
		j++;
	return (ft_substr(s1, i, len - i - j));
}
