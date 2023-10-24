/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:35:08 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/24 17:22:25 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*data_init(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	{
		if (!data)
			return (0);
	}
	data->fd_tmp = 0;
	data->path = addslash(env);
	data->env = env;
	return (data);
}

// int	parser(t_lexer *lexer)
// {
// 	separator_verif()
// 	return (0);
// }

int	routine(char **env)
{
	t_data	*data;

	data = data_init(env);
	data->str = " ";
	while (ft_strncmp(data->str, "stop", 4) != 0)
	{
		data->str = readline("minishell ");
		add_history(data->str);
		lexer(data);
		// execution(lexer(data));
	}
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
