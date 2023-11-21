/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:58:35 by elias             #+#    #+#             */
/*   Updated: 2023/11/21 12:25:25 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nb_heredoc(t_lexer *lexer)
{
	int	lim;

	lim = 0;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == INF_DB)
			lim++;
		lexer = lexer->next;
	}
	return (lim);
}

char	**limiter(t_lexer *lexer, int n)
{
	char **tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (n + 1));
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == LIMITOR)
		{
			tab[i] = lexer->word;
			i++;
		}
		lexer = lexer->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	*commande(t_lexer *lexer)
{
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == CMD)
			return (lexer->word);
		lexer = lexer->next;
	}
	return (NULL);
}

int	nb_arg(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == ARG)
			i++;
		lexer = lexer->next;
	}
	return (i);
}

char	**arg(t_lexer *lexer, char *cmd)
{
	char	**tab;
	int	i;

	i = 1;
	if (!cmd)
		return (NULL);
	tab = malloc(sizeof(char *) * (nb_arg(lexer) + 2));
	if (!tab)
		return (NULL);
	// tab[0] = cmd;
	tab[0] = rm_path(cmd);
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == ARG)
		{
			tab[i] = lexer->word;
			i++;
		}
		lexer = lexer->next;
	}
	tab[i] = NULL;
	return (tab);
}
