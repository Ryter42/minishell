/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:35:08 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/13 16:04:38 by emoreau          ###   ########.fr       */
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
	data->str = NULL;
	data->fd_tmp = 0;
	data->path = addslash(env);
	data->env = cpy_env_with(env, NULL);
	return (data);
}

struct sigaction	*struc_signal_controle_c(void);

int	routine(char **env)
{
	t_data	*data;
	t_cmd	*cmd;

	data = data_init(env);
	while (1)
	{
		// set_signal_action();
		// sigaction(SIGINT, struc_signal_controle_c(), NULL);

		// signal(SIGINT, sigint_handler);
		if (data->str)
			free(data->str);
		data->str = readline("minishell& ");
		add_history(data->str);
		cmd = lexer(data);
		if (cmd)
			execution(cmd);
	}
	return (1);
}

// ne pas oublier de gerer ".." comme entree de commande

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
