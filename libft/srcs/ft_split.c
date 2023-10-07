/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:37:57 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/26 15:20:39 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	nbword(char *s, char c)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if ((s[i]) && s[i] != c)
			w++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (w);
}

static int	lenword(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*wordup(char *str, int len, char c)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * len + 1);
	while (str[i] != c && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	int		i;
	char	**tab;
	char	*str;

	i = 0;
	str = (char *)s;
	j = 0;
	tab = malloc(sizeof(char *) * (nbword(str, c) + 1));
	if (!tab)
		return (NULL);
	while (str[i] && j < nbword(str, c))
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] && str[i] != c)
			tab[j] = wordup(&str[i], lenword(&str[i], c), c);
		while (str[i] != c && str[i])
			i++;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
