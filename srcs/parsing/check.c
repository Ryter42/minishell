/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 23:51:51 by elias             #+#    #+#             */
/*   Updated: 2023/10/22 02:55:51 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_before_pipe(t_lexer *lexer)
{
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == CMD)
			return (1);
		lexer = lexer->prev;
	}
	return (0);
}

int	cmd_after_pipe(t_lexer *lexer)
{
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == CMD)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

int	pipe_error(t_lexer *lexer)
{
	if (cmd_before_pipe(lexer) == 0 || cmd_after_pipe(lexer) == 0)
		return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
	else
		return (1);
}

int	check_pipe(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->word[0] == '|')
		{
			if (!pipe_error(lexer))
				return (0);
		}
		lexer = lexer->next;
	}
	return (1);
}

int check(t_lexer *lexer)
{
	if (!check_separator(lexer))
		return (0);
	// if (!check_pipe(lexer))
	// 	return (0);
	return (1);
}