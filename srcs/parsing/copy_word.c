/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:35:08 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/18 19:52:50 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *quote_word(char *str, int *i, char c)
{
	char	*res;
	int		index;
	int		len;

	index = 0;
	len = quote_len(str, *i, c);
	res = malloc(sizeof(char) * len + 1);
	while(index < len)
	{
		res[index] = str[*i];
		index++;
		(*i)++;
	}
	res[index] = 0;
	return (res);
}

// char *dquote_word(char *str, int *i)
// {
// 	char	*res;
// 	int		index;
// 	int		len;

// 	index = 0;
// 	len = dquote_len(str, *i);
// 	res = malloc(sizeof(char) * len + 1);
// 	while(index < len)
// 	{
// 		res[index] = str[*i];
// 		index++;
// 		(*i)++;
// 	}
// 	res[index] = 0;
// 	return (res);
// }

char *normal_word(char *str, int *i)
{
	char	*res;
	int		len;
	int		index;

	index = 0;
	len = word_len(str, *i);
	res = malloc(sizeof(char) * len + 1);
	while (index < len)
	{
		res[index] = str[(*i)];
		index++;
		(*i)++;
	}
	res[index] = 0;
	return (res);
}

char	*find_sep(char *str, int *i)
{
	char	*res;
	int		len;
	int		index;

	index = 0;
	len = separator_len(str, *i);
	res = malloc(sizeof(char) * len + 1);
	while(index < len)
	{
		res[index] = str[(*i)];
		index++;
		(*i)++;
	}
	res[index] = 0;
	return (res);
}

char	*find_word(char *str, int *i)
{
	if (is_quote(str[*i]) == 1)
		return(quote_word(str, i, str[*i]));
	// if (str[*i] == '"')
	// 	return(dquote_word(str, i));
	else
		return(normal_word(str, i));
}
