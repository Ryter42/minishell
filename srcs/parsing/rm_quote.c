/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:54:24 by elias             #+#    #+#             */
/*   Updated: 2023/10/24 19:54:37 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	num_quote(char *str)
{
	int		i;
	int num;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			find_quote(str, &i);
			num = num + 2;
		}
		if (str[i] == '"')
		{
			i++;
			find_dbquote(str, &i);
			num = num + 2;
		}
		i++;
	}
	return (num);
}

int	copy_in_quote(char *str, char *str2, int *i, int *i2)
{
	char c;

	c = str[*i];
	(*i)++;
	while (str[*i] != c)
	{
		str2[*i2] = str[*i];
		(*i)++;
		(*i2)++;
	}
	(*i)++;
	return (1);
}

char	*line_without_quote(char *str)
{
	char *res;
	int i;
	int i2;

	i = 0;
	i2 = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1 - num_quote(str)));
	while (str[i])
	{
		if (is_quote(str[i]) == 1)
			copy_in_quote(str, res, &i, &i2);
		else
		{
			res[i2] = str[i];
			i++;
			i2++;
		}
	}
	res[i2] = 0;
	return(free(str), res);
}

void	rm_quote(t_lexer *lexer)
{
	int	i;

	while (lexer)
	{
		i = 0;
		while (lexer->word[i])
		{
			if (is_quote(lexer->word[i]) == 1)
			{
				lexer->word = line_without_quote(lexer->word);
				break;
			}
			i++;
		}
		lexer = lexer->next;
	}
}