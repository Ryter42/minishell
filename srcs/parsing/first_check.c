/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:11:11 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/20 20:04:28 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int first_check(char *str)
{
	if (!quote_verif(str))
		return (1);
	if (!metachar_verif(str))
		return (1);
	return (0);
}

int bt_quote(char *str, int i)
{
	int		index;

	index = 0;
	// while (index <= i)
	while (str[index])
	{
		if (str[index] == '\'')
		{
			index++;
			find_quote(str, &index);
			// if (index > i)
				// return (i);
		}
		if (str[index] == '"')
		{
			index++;
			find_dbquote(str, &index);
			// if (index > i)
			// 	return (1);
		}
		if (index == i)
			return (0);
		index++;
	}
	return (1);
}

int	metachar_verif(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == ')' && bt_quote(str, i) == 0)
		{
			printf("minishell: syntax error near unexpected token `)'\n");
			return (2);
		}
		else if (str[i] == '(' && bt_quote(str, i) == 0)
		{
			printf("minishell: syntax error near unexpected token `('\n");
			return (2);
		}
		i--;
	}
	if (metachar_verif2(str) == 2)
		return (2);
	else
		return (0);
}

// int	is_metachar(char c)
// {
// 	if (c == ')' || c == '(' || c == '&' || c == ';')
// 		return (1);
// 	else
// 		return (0);
// }


int	metachar_verif2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '&' && bt_quote(str, i) == 0)
		{
			printf("minishell: syntax error near unexpected token `&'\n");
			return (2);
		}
		else if (str[i] == ';' && bt_quote(str, i) == 0)
		{
			printf("minishell: syntax error near unexpected token `;'\n");
			return (2);
		}
		i++;
	}
	return (0);
}
