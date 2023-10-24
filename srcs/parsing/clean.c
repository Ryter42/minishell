/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 03:55:20 by elias             #+#    #+#             */
/*   Updated: 2023/10/24 23:18:20 by emoreau          ###   ########.fr       */
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
	while (lexer && lexer->token != PIPE && lexer->token != SUP
		&& lexer->token != SUP_DB)
		lexer = lexer->prev;
	if (lexer && lexer->token != PIPE)
	{
		cmd->outfile = lexer->next->word;
		if (lexer->token == SUP)
			cmd->add_out = 0;
		else
			cmd->add_out = 1;
		// create_outfile(lexer);
	}
	else
	{
		cmd->outfile = NULL;
		cmd->add_out = 0;
	}
}

char	*path_cmd(t_data *data, char *cmd)
{
	char	*path_cmd;
	int		file;

	(void)data;
	if (is_there_slash(cmd) == 0)
	{
		file = findpath(data, cmd);
		if (file < 0)
			return (NULL);
		path_cmd = ft_strjoin(data->path[file], cmd);
		return (path_cmd);
	}
	else
		return (cmd);
}

t_cmd	*create_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->data = lexer->data;
	cmd->heredoc = nb_heredoc(lexer);
	if (cmd->heredoc)
		cmd->limiter = limiter(lexer, cmd->heredoc);
	else
		cmd->limiter = NULL;
	cmd->cmd = path_cmd(lexer->data, commande(lexer));
	cmd->arg = arg(lexer, cmd->cmd);
	cmd->infile = infile(lexer);
	outfile(lexer, cmd);
	return (cmd);
}

t_cmd	*lst_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

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
		while (lexer && lexer->token != PIPE)
			lexer = lexer->next;
		if (lexer)
			lexer = lexer->next;
	}
	if (cmd)
		cmd->next = NULL;
	return (tmp);
}

void	printab(char **tab, char *var)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s ", var);
		printf("%d = %s ", i, tab[i]);
		i++;
	}
	printf("\n");
}

t_cmd	*clean_cmd(t_lexer *lexer)
{
	t_cmd *cmd;
	t_cmd *tmp;

	lexer = expand(lexer, lexer->data->env);

	rm_quote(lexer);
	cmd = lst_cmd(lexer);
	tmp = cmd;
	// while (cmd)
	// {
		// 	printf("cmd = %s\n", cmd->cmd);
		// 	printf("infile = %s\n", cmd->infile);
		// 	printf("heredoc = %d\n", cmd->heredoc);
		// 	if (cmd->limiter)
		// 		printab(cmd->limiter, "limiter");
		// 	printab(cmd->arg, "arg");
		// printf("outfile = %s\n", cmd->outfile);
		// 	printf("add = %d\n", cmd->add_out);
		// 	printf("\nnew cmd\n");
	// 	cmd = cmd->next;
	// }
	return (tmp);
}