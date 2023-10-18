/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:37:39 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/18 21:46:28 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	whatoken(t_lexer *lexer)
{
	
}

void	give_token(t_lexer *lexer)
{
	while (lexer)
	{
		lexer->token = whatoken(lexer);
		lexer = lexer->next;
	}
}
