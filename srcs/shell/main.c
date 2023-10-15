/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:35:08 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/15 04:29:59 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_separator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

int	num_separator(char *str, char *quote)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (is_separator(str[i]) == 1)
			res++;
		i++;
	}
	return (res);
}

void add_space(char *str, char c, int i)
{
	str[i] = ' ';
	i++;
	str[i] = c;
	i++;
	str[i] = ' ';
}

char	*space_separator(char *str, char *quote)
{
	char *res;
	int	i;
	int	j;

	j = 0;
	i = 0;
	res = malloc(sizeof(ft_strlen(str) + (num_separator(str, quote) * 2) + 1));
	while (str[i])
	{
		if (is_separator(str[i]) == 1)
		{
			add_space(res, str[i], j);
			j = j + 3;
			i++;
		}
		else
		{
			res[j] = str[i];
			i++;
			j++;
		}
	}
	res[j] = 0;
	free(str);
	return (res);
}

// t_lexer create_lst(t_data *data)
// {
// 	t_lexer *lexer
	
// }

t_data	*ft_lexer(t_data *data)
{
	// int	i = 0;
	data->tab = ft_split(data->str, " ");
	// data->lexer = create_lst(data);
	return (data);
}

int	numchar(char *str, char c)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			res++;
		i++;
	}
	return (res);
}

int	find_quote(char *str, char *quote, int *i)
{
	while (str[*i] != '\'' || str[*i - 1] == '\\')
	{
		if (str[*i] == 0)
			return (0);
		quote[*i] = '1';
		(*i)++;
	}
	quote[*i] = '3';
	(*i)++;
	return (1);
}

int	find_dbquote(char *str, char *quote, int *i)
{
	while (str[*i] != '"' || str[*i - 1] == '\\')
	{
		if (str[*i] == 0)
			return (0);	
		quote[*i] = '1';
		(*i)++;
	}
	quote[*i] = '2';
	(*i)++;
	return (1);
}

char	*quote(char *str)
{
	// if (numchar(str, '\'') % 2 == 1)
	// 	return (0);
	// if (numchar(str, '"') % 2 == 1)
	// 	return (0);
	int		i;
	char	*quote;

	i = 0;
	quote = malloc(sizeof(ft_strlen(str) + 1));
	if (!quote)
		return(NULL);
	while (str[i])
	{
		if ((str[i] == '\'' && i == 0) || (str[i] == '\'' && str[i - 1] != '\\'))
		{
			quote[i] = '3';
			i++;
			// while (str[i] != '\'' || str[i - 1] == '\\')
			// {
			// 	i++;
			// 	if (str[i] == 0)
			// 		return (0);	
			// }
			if (find_quote(str, quote, &i) == 0)
				return (NULL);
		}
		if ((str[i] == '"' && i == 0) || (str[i] == '"' && str[i - 1] != '\\'))
		{
			quote[i] = '2';
			i++;
			// while (str[i] != '"' && str[i - 1] == '\\')
			// {
			// 	i++;
			// 	if (str[i] == 0)
			// 		return (0);	
			// }
			if (find_dbquote(str, quote, &i) == 0)
				return (NULL);
		}
		if (str[i])
			quote[i] = '0';
		else
			quote[i] = 0;
		i++;
	}
	quote[i] = 0;
	return (quote);
}

// int	quote(char *str)
// {
// 	if (veriquote(str) == 0)
// 		return (0);	
// 	return (1);
// }

int parsing(t_data *data)
{
	data->quote = quote(data->str);
	if (!data->quote)
		return (0);
	// space_separator(data->str, data->quote);
	ft_lexer(data);
	return (1);
}

t_data	*first_init(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	{
		if (!data)
			return (0);
	}
	return (data);
}

int	routine(void)
{
	t_data *data;

	data = first_init();
	data->str = readline("minishell ");
	if (parsing(data) == 0)
		return (0);
	// str = ft_lexer(str);
	printf("%s\n", data->str);
	printf("%s\n", data->quote);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	// char *str;
	// char **tab;
	// int i = 0;

	// first_init(data);
	routine();

	
	// while(strcmp("stop", str) != 0)
	// {
	// 	str = readline("minishell->");
	// }

	// tab = ft_split(str, " ");

	// free(str);
}
