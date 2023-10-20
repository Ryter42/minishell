/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:37:39 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/20 21:30:38 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_is_redir(t_token token)
{
	if (token == INF || token == SUP)
		return (1);
	else if (token == INF_DB || token == SUP_DB)
		return (2);
	else
		return (0);
}

t_token token_file(t_token token)
{
	if (token == INF)
		return (INFILE);
	else if (token == INF_DB)
		return (LIMITOR);
	else
		return (OUTFILE);
}

// int	token_is_sep(t_token token)
// {
// 	if (/* condition */)
// 	{
// 		/* code */
// 	}
	
// }

int	has_cmd(t_lexer *lexer)
{
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == CMD)
			return (1);
		lexer = lexer->prev;
	}
	return (0);
}

t_token token_word(t_lexer *lexer)
{
	if (token_is_redir(lexer->prev->token) > 0)
		return (token_file(lexer->prev->token));
	if (has_cmd(lexer) == 0)
		return (CMD);
	else
		return (ARG);
}

t_token	whatoken(t_lexer *lexer)
{
	if (is_separator(lexer->word[0]))
		return (token_sep(lexer));
	else
		return (token_word(lexer));
}

void	give_token(t_lexer *lexer)
{
	while (lexer)
	{
		lexer->token = whatoken(lexer);
		lexer = lexer->next;
	}
}
