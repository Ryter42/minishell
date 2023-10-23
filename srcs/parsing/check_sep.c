/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 02:19:17 by elias             #+#    #+#             */
/*   Updated: 2023/10/22 02:19:31 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sep_error(char *str)
{
	if (str[0] == '|')
	{
		if (ft_strlen(str) > 1)
			return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
	}
	else
	{
		if (ft_strlen(str) > 2)
			return (printf("minishell: syntax error near unexpected token `%c'\n", str[0]), 0);
	}
	return (1);
}

int	redir_error(t_lexer *lexer)
{
	if (lexer->next)
	{
		if (is_separator(lexer->next->word[0]) == 1)
			return(printf("minishell: syntax error near unexpected token `%s'\n", lexer->next->word), 0);
		else
			return (1);
	}
	else
			return(printf("minishell: syntax error near unexpected token `newline'\n"), 0);
}

int	check_separator(t_lexer *lexer)
{
	while (lexer)
	{
		if (is_separator(lexer->word[0]) == 1)
		{
			if (!sep_error(lexer->word))
				return (0);
		}
		if (is_redir(lexer->word[0]) == 1)
		{
			if (!redir_error(lexer))
				return(0);
		}
		lexer = lexer->next;
	}
	return (1);
}
