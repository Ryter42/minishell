/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 03:55:20 by elias             #+#    #+#             */
/*   Updated: 2023/10/23 17:00:00 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*infile(t_lexer *lexer)
{
	// lexer = find_last_infile(lexer);

	while (lexer->next && lexer->token != PIPE)
		lexer = lexer->next;
	while (lexer && lexer->token != INF && lexer->token != INF_DB)
		lexer = lexer->prev;
	if (lexer && lexer->token == INF)
		return (lexer->next->word);
	return (NULL);
}

void	create_outfile(t_lexer *lexer)
{
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == SUP || lexer->token == SUP_DB)
			open(lexer->next->word, O_RDWR | O_CREAT | O_TRUNC, 0644);
		lexer = lexer->prev;
	}
}

void	outfile(t_lexer *lexer, t_cmd *cmd)
{
	while (lexer->next && lexer->token != PIPE)
		lexer = lexer->next;
	while (lexer && lexer->token != SUP && lexer->token != SUP_DB)
		lexer = lexer->prev;
	if (lexer)
	{
		cmd->outfile = lexer->next->word;
		if (lexer->token == SUP)
			cmd->add_out = 0;
		else
			cmd->add_out = 1;
		// create_outfile(lexer);
	}
}

t_cmd	*create_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	cmd->heredoc = heredoc(lexer);
	if (cmd->heredoc)
		cmd->limiter = limiter(lexer, cmd->heredoc);
	else
		cmd->limiter = NULL;
	cmd->cmd = commande(lexer);
	cmd->arg = arg(lexer);
	cmd->infile = infile(lexer);
	outfile(lexer, cmd);
	return (cmd);
}

t_cmd	*lst_cmd(t_lexer *lexer)
{
	t_cmd *cmd;
	t_cmd *tmp;

	cmd = create_cmd(lexer);
	tmp = cmd;
	while (lexer && lexer->token != PIPE)
		lexer = lexer->next;
	if (lexer)
		lexer = lexer->next;
	while (lexer)
	{
		cmd->next = create_cmd(lexer);
		cmd = cmd->next;
		while (lexer && lexer->token !=	 PIPE)
			lexer = lexer->next;	
		if (lexer)
			lexer = lexer->next;
	}
	// cmd->next = NULL;
	return (tmp);
}

void	printab(char **tab, char *var)
{
	int	i = 0;
	while (tab[i])
	{
		printf("%s ", var);
		printf("%d = %s ", i, tab[i]);
		i++;
	}
		printf("\n");
}



t_cmd	*clean_cmd(t_lexer *lexer, char **env)
{
	t_cmd *cmd;

	expand(lexer, env);
	rm_quote(lexer);
	cmd = lst_cmd(lexer);
	while (cmd)
	{
		printf("cmd = %s\n", cmd->cmd);
		printf("infile = %s\n", cmd->infile);
		printf("heredoc = %d\n", cmd->heredoc);
		if (cmd->limiter)
			printab(cmd->limiter, "limiter");
		printab(cmd->arg, "arg");
		printf("outfile = %s\n", cmd->outfile);
		printf("add = %d\n", cmd->add_out);
		printf("\nnew cmd\n");
		cmd = cmd->next;
	}
	return (cmd);
}