/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:35:08 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/18 16:30:45 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*data_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	{
		if (!data)
			return (0);
	}
	return (data);
}

int	routine(char **env)
{
	(void)env;
	t_data	*data;

	data = data_init();
	data->str = readline("minishell ");
	
	// if (lexer(data) == 0)
	// 	return (0);
	data->lexer = lexer(data);
	// str = ft_lexer(str);
	// printf("%s\n", data->str);
	// printf("%s\n", data->quote);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	// char *str;
	// char **tab;
	// int i = 0;
	// first_init(data);
	routine(env);
	// while(strcmp("stop", str) != 0)
	// {
	// 	str = readline("minishell->");
	// }
	// tab = ft_split(str, " ");
	// free(str);
}
