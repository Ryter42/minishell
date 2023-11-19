/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:26:34 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/18 23:26:11 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quote(char *str, int *i)
{
	while (str[*i] != '\'')
	{
		if (str[*i] == 0)
			return (0);
		// quote[*i] = '1';
		(*i)++;
	}
	// quote[*i] = '3';
	(*i)++;
	return (1);
}

int	find_dbquote(char *str, int *i)
{
	while (str[*i] != '"')
	{
		if (str[*i] == 0)
			return (0);
		// quote[*i] = '1';
		(*i)++;
	}
	// quote[*i] = '2';
	(*i)++;
	return (1);
}

int	quote_verif(char *str)
{
	int		i;
	// char	*quote;

	// if (numchar(str, '\'') % 2 == 1)
	// 	return (0);
	// if (numchar(str, '"') % 2 == 1)
	// 	return (0);
	i = 0;

	// quote = malloc(sizeof(len + 1));
	// if (!quote)
	// 	return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			// quote[i] = '3';
			i++;
			// while (str[i] != '\'' || str[i - 1] == '\\')
			// {
			// 	i++;
			// 	if (str[i] == 0)
			// 		return (0);
			// }
			if (find_quote(str, &i) == 0)
				return (printf("minishell: syntax error missing token `''\n"),0);
		}
		else if (str[i] == '"')
		{
			// quote[i] = '2';
			i++;
			// while (str[i] != '"' && str[i - 1] == '\\')
			// {
			// 	i++;
			// 	if (str[i] == 0)
			// 		return (0);
			// }
			if (find_dbquote(str, &i) == 0)
				return (printf("minishell: syntax error missing token `\"'\n"),0);
		}
		else
			i++;
	}
	return (1);
}