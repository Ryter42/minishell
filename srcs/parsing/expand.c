/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 03:10:31 by elias             #+#    #+#             */
/*   Updated: 2023/11/19 19:51:01 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_var(char **env, t_lexer *lexer, char *var_name)
{
	char	*var;
	char	*tmp;
	int		len_name;
	int		len_var;
	int		index;
	int		index_var;
	int		index_word;

// 	lexer->data->status
	index_word = 0;
	index_var = 0;
	index = 0;
	len_name = ft_strlen(var_name);
	var = find_var(env, var_name, len_name, lexer->data->status);
	len_var = ft_strlen(var);
	tmp = malloc(sizeof(char) * (len_var - len_name + ft_strlen(var) + 1));
	while (lexer->word[index_word] != '$')
	{
		tmp[index] = lexer->word[index_word];
		index_word++;
		index++;
	}
	if (var)
	{
		while (var[index_var])
		{
			tmp[index] = var[index_var];
			index_var++;
			index++;
		}
	}
	index_word++;
	// while (lexer->word[index_word] && lexer->word[index_word] != '"' && lexer->word[index_word] != '$')
	// 	index_word++;

	while (lexer->word[index_word + len_var + 1])
	{
		tmp[index] = lexer->word[index_word + len_var + 1];
		index++;
		index_word++;
	}
	tmp[index] = 0;
	free(lexer->word);
	free_str(&var);
	free_str(&var_name);
	lexer->word = tmp;
}

void	variable(t_lexer *lexer, char **env)
{
	int	i;

	i = 0;
	while (lexer->word[i])
	{
		if (lexer->word[i] == '$' && !bt_sp_quote(lexer->word, i))
		{
			replace_var(env, lexer, var_name(lexer->word, i + 1));
			i = 0;
		}
		else
			i++;
	}
}

t_lexer	*expand(t_lexer *lexer, char **env)
{
	t_lexer *tmp;

	tmp = lexer;
	while (lexer)
	{
		if (!is_separator(lexer->word[0]))
			variable(lexer, env);
		lexer = lexer->next;
	}
	return (tmp);
	// 	while (tmp)
	// {
	// 	// if (tmp->word)
	// 	printf("%s\n", tmp->word);
	// 	tmp = tmp->next;
	// }
}
