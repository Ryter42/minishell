/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 03:22:29 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/15 04:48:24 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	shell_nbword(char *s, char *charset, char *quote)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || quote[i] != '0'))
			i++;
		if ((s[i]) && s[i] != ' ' && quote[i] == '0')
			w++;
		while (s[i] && s[i] != ' ')
			i++;
	}
	return (w);
}

int	shell_lenword(char *s, char *str)
{
	int	i;

	i = 0;
	while (s[i] && charin_str(s[i], str) == 0)
		i++;
	return (i);
}

char	*shell_wordup(char *str, int len, char *charset)
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

char	**shell_split(char const *s, char *quote, char *charset)
{
	int		j;
	int		i;
	char	**tab;
	char	*str;

	i = 0;
	str = (char *)s;
	j = 0;
	tab = malloc(sizeof(char *) * (shell_nbword(str, charset) + 1));
	if (!tab)
		return (NULL);
	while (str[i] && j < shell_nbword(str, charset))
	{
		while (charin_str(str[i], charset) == 1 && str[i])
			i++;
		if (str[i] && charin_str(str[i], charset) == 0)
			tab[j] = shell_wordup(&str[i], shell_lenword(&str[i], charset), charset);
		while (charin_str(str[i], charset) == 0 && str[i])
			i++;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
