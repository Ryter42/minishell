/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:37:57 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/07 20:22:05 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	charin_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	nbword(char *s, char *str)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && charin_str(s[i], str) == 1)
			i++;
		if ((s[i]) && charin_str(s[i], str) == 0)
			w++;
		while (s[i] && charin_str(s[i], str) == 0)
			i++;
	}
	return (w);
}

static int	lenword(char *s, char *str)
{
	int	i;

	i = 0;
	while (s[i] && charin_str(s[i], str) == 0)
		i++;
	return (i);
}

static char	*wordup(char *str, int len, char *charset)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * len + 1);
	while (charin_str(str[i], charset) == 0 && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char *charset)
{
	int		j;
	int		i;
	char	**tab;
	char	*str;

	i = 0;
	str = (char *)s;
	j = 0;
	tab = malloc(sizeof(char *) * (nbword(str, charset) + 1));
	if (!tab)
		return (NULL);
	while (str[i] && j < nbword(str, charset))
	{
		while (charin_str(str[i], charset) == 1 && str[i])
			i++;
		if (str[i] && charin_str(str[i], charset) == 0)
			tab[j] = wordup(&str[i], lenword(&str[i], charset), charset);
		while (charin_str(str[i], charset) == 0 && str[i])
			i++;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
