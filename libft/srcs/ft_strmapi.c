/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:00:03 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/24 18:54:53 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	char	*ss;
	int		i;

	i = 0;
	ss = (char *) s;
	str = malloc(sizeof(char) * ft_strlen(ss) + 1);
	while (ss[i])
	{
		str[i] = f(i, ss[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
