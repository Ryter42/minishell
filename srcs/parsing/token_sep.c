/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:26:20 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/20 20:27:52 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	token_inf(char *str)
{
	if (ft_strlen(str) == 1)
		return (INF);
	else
		return	(INF_DB);
}

t_token	token_sup(char *str)
{
	if (ft_strlen(str) == 1)
		return (SUP);
	else
		return	(SUP_DB);
}

t_token	token_sep(t_lexer *lexer)
{
	if (lexer->word[0] == '<')
		return	(token_inf(lexer->word));
	if (lexer->word[0] == '>')
		return	(token_sup(lexer->word));
	else
		return (PIPE);
}
