/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:41:34 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/18 21:45:53 by emoreau          ###   ########.fr       */
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
	lexer->word = find_token(data, i);
	return (lexer);
}

t_lexer	*lst_cmd(t_data *data)
{
	t_lexer *lexer;
	int i;
	int	prev;

	prev = 0;
	i = 0;
	int len = ft_strlen(data->str);
	
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
			lexer->next->prev = lexer;
			lexer = lexer->next;
		}
	}
	lexer->next = NULL;
	while (lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

t_lexer	*lexer(t_data *data)
{
	t_lexer *lexer;

	if (quote(data->str) == 0)
		return (0);
	lexer = lst_cmd(data);;
	give_token(lexer);
	// test
	// t_lexer *tmp;

	while (lexer)
	{
		printf("%s\n", lexer->word);
		// printf("%s\n", lexer->word);
		// tmp = lexer;
		lexer = lexer->next;
	}
	// while(tmp)
	// {
	// 	printf("%s\n", tmp->word);
	// 	tmp = tmp->prev;	
	// }
	return (lexer);
}