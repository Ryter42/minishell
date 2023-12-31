/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:41:34 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/20 19:32:20 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *find_token(t_data *data, int *i)
{
	// int	i;

	// i = 0;
	// while (data->str[*i])
	// {
		while (is_space(data->str[*i]) == 1)
			(*i)++;
		if (!data->str[*i])
			return (NULL);
		if (is_separator(data->str[*i]) == 1)
			return(find_sep(data->str, i));	
		else
			return(find_word(data->str, i));
	// }
}

t_lexer	*create_node(t_data *data, int *i)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	// if (find_token(data, i))
	lexer->word = find_token(data, i);
	lexer->data = data;
	if (lexer->word)
		return (lexer);
	else
	{
		free(lexer);
		return (NULL);
	}
}

t_lexer	*lst_lexer(t_data *data)
{
	t_lexer *lexer;
	int len; 
	int i;
	int	prev;

	prev = 0;
	i = 0;
	len = ft_strlen(data->str);
	if (!len)
		return (NULL);
	while (i < len)
	{
		if (prev == 0)
		{
			lexer = create_node(data, &i);
			lexer->prev = NULL;
			prev = 1;
		}
		else
		{
			lexer->next = create_node(data, &i);
			if (lexer->next)
			{
				lexer->next->prev = lexer;
				lexer = lexer->next;
			}
		}
	}
	if (lexer)
		lexer->next = NULL;
	while (lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

t_cmd	*lexer(t_data *data)
{
	t_lexer *lexer;
	t_cmd	*cmd;
	int		OK;

	lexer = NULL;
	OK = first_check(data->str);
	if (!OK)
	{
		data->status = 2;
		return (NULL);
	}
	lexer = lst_lexer(data);
	if (!lexer)
		return (NULL);
	give_token(lexer);
	OK = check(lexer);
		// data->status = 2;
		// return (NULL);
	// rm_quote
	// test
	// if (!lexer || lexer == NULL)
	// 	return (NULL);
	// t_lexer *tmp;
	// while (lexer)
	// {
	// 	if (lexer->word)
	// 		// printf("%s le token est %d\n", lexer->word, lexer->token);
	// 	// printf("%s\n", lexer->word);
	// 	// tmp = lexer;
	// 	lexer = lexer->next;
	// }
	// while(tmp)
	// {
	// 	// printf("%s\n", tmp->word);
	// 	tmp = tmp->prev;
	// }
	// printf("data = %p\n", data);
	if (OK)
		cmd = clean_cmd(lexer);
	else
	{
		data->status = 2;
		cmd = NULL;
	}
	return (cmd);
}