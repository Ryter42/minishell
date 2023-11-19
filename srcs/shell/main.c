/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:35:08 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/19 20:08:09 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	status[2];

char	**create_env(void)
{
	char	**env;

	env = malloc (sizeof(char *) * 2);
	if (!env)
		return (NULL);
	*env = getcwd(*env, 0);
	env[1] = NULL;
	return (env);
}

char **init_env(char **env)
{
	if (!env)
		return (create_env());
	else
		return (cpy_env_with(env, NULL));
}

t_data	*data_init(char **env)
{
	t_data	*data;

	// status[1] = 0;
	data = malloc(sizeof(t_data));
	{
		if (!data)
			return (0);
	}
	data->str = NULL;
	// data->pid = NULL;
	data->fd_tmp = 0;
	data->env = init_env(env);
	data->path = addslash(data->env);
	// printf("path = %p\n", data->path);
	return (data);
}

// struct sigaction	*struc_signal_controle_c(void);

int	routine(char **env)
{
	t_data	*data;
	t_cmd	*cmd;
	// int		status;

	// status = 0;
	data = data_init(env);
	data->status = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		// signal(SIG, signal_ctrl_backslash);
		signal(SIGINT, signal_ctrl_c);
		// set_signal_action();
		// sigaction(SIGINT, struc_signal_controle_c(), NULL);

		// signal(SIGINT, sigint_handler);
		if (data->str)
			free(data->str);
		data->str = readline("minishell& ");
		if (data->str == NULL)
			break;
		if (!*(data->str))
			continue;
		// data->str = get_next_line(0 , 1);
		add_history(data->str);
		// printf("data = %p\n", data);

		cmd = lexer(data);
		// printf("cmd->data = %p\n", cmd->data);
		
		// printf("cmd->next = %p\n", cmd->next);
		// printf("address de data dans routine = %p\n", cmd->data);
		// if (data->status == 2)
		// 	free_cmd(cmd);
		if (cmd)
			cmd->data->status = execution(cmd);
	}
	printf("fin du programme\n");
	// free_all(cmd);
	free_data(data);
	return (1);
}

// ne pas oublier de gerer ".." comme entree de commande

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (!isatty(STDIN_FILENO))
	{
		write(2, "minishell: stdin is not a tty", 30);
		exit(1);
	}
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

// proteger les write de echo pour quand on ecrit dan un fichier ou on peut plus
// proteger quand y'a plus d'entrer standard
// leak quand il y a une erreur de parsing et qu'on fait control D
// command not found s'ecrit avant le heredoc
// ajouter status
// remplacer le path de cmd par le nom seul pour imiter exactement le shell
// lancer le checker de l'entree standard a chaque readline
// control c apres avoir fait la commande "cat" qui r'affiche 2 fois le prompt
// probleme avec la commande echo "$USER $?" ca viens de la commande var replace
/*
Leaks avec ces commandes : 
-
-
*/