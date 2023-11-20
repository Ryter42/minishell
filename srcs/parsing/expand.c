/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 03:10:31 by elias             #+#    #+#             */
/*   Updated: 2023/11/20 18:30:21 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	replace_var(char **env, t_lexer *lexer, char *var_name)
// {
// 	char	*var;
// 	char	*tmp;
// 	int		len_name;
// 	int		len_var;
// 	int		index;
// 	int		index_var;
// 	int		index_word;

// // 	lexer->data->status
// 	index_word = 0;
// 	index_var = 0;
// 	index = 0;
// 	len_name = ft_strlen(var_name);
// 	var = find_var(env, var_name, len_name, lexer->data->status);
// 	len_var = ft_strlen(var);
// 	tmp = malloc(sizeof(char) * (ft_strlen(lexer->word) + len_var - len_name + 1));
// 	if (!tmp)
// 		return ;
// 	while (lexer->word[index_word] != '$')
// 	{
// 		tmp[index] = lexer->word[index_word];
// 		index_word++;
// 		index++;
// 	}
// 	if (var)
// 	{
// 		while (var[index_var])
// 		{
// 			tmp[index] = var[index_var];
// 			index_var++;
// 			index++;
// 		}
// 	}
// 	index_word++;
// 	// while (lexer->word[index_word] && lexer->word[index_word] != '"' && lexer->word[index_word] != '$')
// 	// 	index_word++;

// 	while (lexer->word[index_word + len_name])
// 	{
// 		tmp[index] = lexer->word[index_word + len_name];
// 		index++;
// 		index_word++;
// 	}
// 	tmp[index] = 0;
// 	free(lexer->word);
// 	free_str(&var);
// 	free_str(&var_name);
// 	lexer->word = tmp;
// }

int cpy_begin(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '$')
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}

int cpy_var(char *dest, char *var, int index)
{
	int	i;

	i = 0;
	while (var[i])
	{
		dest[index + i] = var[i];
		i++;
	}
	return (i);
}

void	cpy_end(char *dest, char *src, int index_dest, int index_src)
{
	while (src[index_src])
	{
		dest[index_dest] = src[index_src];
		index_dest++;
		index_src++;
	}
	dest[index_dest] = 0;
}

void	replace_var(char **env, t_lexer *lexer, char *var_name)
{
	char	*var;
	char	*tmp;
	int		len_name;
	int		index;
	int		index_word;

	index_word = 0;
	index = 0;
	len_name = ft_strlen(var_name);
	var = find_var(env, var_name, len_name, lexer->data->status);
	tmp = malloc(sizeof(char) * (ft_strlen(lexer->word) + ft_strlen(var) - len_name + 1));
	if (!tmp)
		return ;
	index_word = cpy_begin(tmp, lexer->word);
	if (var)
		index = index_word + cpy_var(tmp, var, index_word);
	else
		index = index_word;
	cpy_end(tmp, lexer->word, index, index_word + len_name + 1);
	free_str(&lexer->word);
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
		// printf("-----------------------------------------------%c\n", lexer->word[i]);
		if (lexer->word[i] == '$' && !bt_sp_quote(lexer->word, i))
		{
			replace_var(env, lexer, var_name(lexer->word, i + 1));
			// i = 0;
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
