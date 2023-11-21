/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 03:55:20 by elias             #+#    #+#             */
/*   Updated: 2023/11/21 15:39:06 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_infile(t_lexer *lexer)
{
	while (lexer && lexer->token != PIPE)
	{
		// if (lexer->token == INF || lexer->token == INF_DB)
		if (lexer->token == INF)
			free(lexer->next->word);
		lexer = lexer->prev;
	}
}

void	free_outfile(t_lexer *lexer)
{
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == SUP || lexer->token == SUP_DB)
			free(lexer->next->word);
		lexer = lexer->prev;
	}
}

char	*infile(t_lexer *lexer)
{
	// lexer = find_last_infile(lexer);
	while (lexer->next && lexer->next->token != PIPE)
		lexer = lexer->next;
	while (lexer && lexer->token != PIPE && lexer->token != INF
		&& lexer->token != INF_DB)
		lexer = lexer->prev;
	if (lexer && lexer->token == INF)
	{
		free_infile(lexer->prev);
		return (lexer->next->word);
	}
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
	while (lexer->next && lexer->next->token != PIPE)
		lexer = lexer->next;
	// while (lexer && lexer->token != SUP && lexer->token != SUP_DB)
	while (lexer && lexer->token != PIPE && lexer->token != SUP
		&& lexer->token != SUP_DB)
		lexer = lexer->prev;
	if (lexer && lexer->token != PIPE)
	{
		cmd->outfile = lexer->next->word;
		free_outfile(lexer->prev);
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

	// if (!cmd)
	// 	return (NULL);
	if (is_there_slash(cmd) == 0)
	{
		file = findpath(data, cmd);
		if (file < 0)
			return (cmd);
			// return (free(cmd), NULL);
		path_cmd = ft_strjoin(data->path[file], cmd);
		free(cmd);
		// cmd = NULL;
		return (path_cmd);
	}
	else
		return (cmd);
}

void	cmd_init(t_cmd *cmd, char *command)
{
	if (!command)
	{
		cmd->cmd = NULL;
		cmd->bultin = -1;
		return ;
	}
	if (is_bultin(command) == 1)
	{
		cmd->bultin = 1;
		cmd->cmd = command;
	}
	else
	{
		cmd->bultin = 0;
		cmd->cmd = path_cmd(cmd->data, command);
	}
}

t_cmd	*create_cmd(t_lexer *lexer, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	// cmd->pid = NULL;
	cmd->fd_heredoc = -1;
	cmd->data = lexer->data;
	cmd->heredoc = nb_heredoc(lexer);
	if (cmd->heredoc)
		cmd->limiter = limiter(lexer, cmd->heredoc);
	else
		cmd->limiter = NULL;
	// cmd->cmd = path_cmd(lexer->data, commande(lexer));
	// printf("cmd->data = %p\n", cmd->data);
	cmd_init(cmd, commande(lexer));
	cmd->arg = arg(lexer, cmd->cmd);
	cmd->infile = infile(lexer);
	outfile(lexer, cmd);
	cmd->prev = prev;
	// dprintf(2, "infile : %p\n", cmd->infile);
	// dprintf(2, "outfile : %p\n", cmd->outfile);

	return (cmd);
}

t_cmd	*give_adress()
{
	static t_cmd cmd = {0};

	return (&cmd);
}

t_cmd	*lst_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	tmp = give_adress();
	cmd = create_cmd(lexer, NULL);
	tmp->next = cmd;
	while (lexer && lexer->token != PIPE)
		lexer = lexer->next;
	if (lexer)
		lexer = lexer->next;
	while (lexer)
	{
		cmd->next = create_cmd(lexer, cmd);
		cmd = cmd->next;
		while (lexer && lexer->token != PIPE)
			lexer = lexer->next;
		if (lexer)
			lexer = lexer->next;
	}
	if (cmd)
		cmd->next = NULL;
	return (tmp->next);
}

int	token_is_sep(t_token token)
{
	if (token == PIPE || token == INF || token == INF_DB || token == SUP
		|| token == SUP_DB)
		return (1);
	else
		return (0);
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		if (token_is_sep(lexer->token) == 1)
		{
			// printf("word = %s ; token = %d\n", lexer->word, lexer->token);
			// if (is_separator(lexer->word[0]))
			// printf("free : %s\n", lexer->word);
			free(lexer->word);
		}
		else
			lexer->word = NULL;
		tmp = lexer;
		lexer = lexer->next;
		free(tmp);
	}
}

t_cmd	*clean_cmd(t_lexer *lexer)
{
	t_cmd *cmd;

	lexer = expand(lexer, lexer->data->env);

	rm_quote(lexer);
	cmd = lst_cmd(lexer);
	// printf("address de data dans clean_cmd = %p\n", cmd->data);
	// printf("cmd->next = %p\n", cmd->next);
	
	free_lexer(lexer);
	return (cmd);
}