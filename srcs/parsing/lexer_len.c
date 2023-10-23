/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:31:42 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/22 01:37:38 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int tokend(char *str, int i)
// {
// 	if (stop_token(str[i]) == 1)
// 		return (1);
// 	else
// 		return (0);
// }

int	word_len(char *str, int i)
{
	int	len;

	len = 0;
	// while (str[i] && (is_space(str[i]) == 0 && is_separator(str[i] == 0)))
	while (stop_token(str[i]) == 0)
	// while (str[i])
	{
		if (is_quote(str[i]) == 1)
		{
			len = len + quote_len(str, i, str[i]);
			i = i + quote_len(str, i, str[i]);
		}
		else
		{	
			len++;
			i++;
		}
	}
	return (len);
}

int	separator_len(char *str, int i)
{
	char c;
	int	len;

	len = 0;
	c = str[i];
	while(str[i] == c)
	{
		len++;
		i++;
	}
	return (len);
}

int	quote_end(char *str, int i, char c)
{
	if (str[i] == c && (stop_token(str[i + 1]) == 1))
		return (1);
	else
		return (0);
}

int	quote_len(char *str, int i, char c)
{
	int	len;
	int	quote;

	quote = 0;
	len = 1;
	i++;
	while (quote_end(str, i, c) == 0 && (quote == 0 || stop_token(str[i]) == 0))
	{
		if (str[i] == c)
			quote = 1;
		len++;	
		i++;
	}
	if (is_quote(str[i]) == 1)
		len++;
	return (len);
}
