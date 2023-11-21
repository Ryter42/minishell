/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:35:08 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/21 21:25:39 by emoreau          ###   ########.fr       */
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
	// *env = getcwd(*env, 0);
	*env = getcwd(NULL, 0);
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
		if (data->str == NULL || !isatty(STDIN_FILENO))
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
		signal(SIGINT, SIG_IGN);
		if (cmd)
			execution(cmd);
	}
	printf("fin du programme\n");
	// free_all(cmd);
	// status = data->status;
	free_data(data);
	return (1);
}

// ne pas oublier de gerer ".." comme entree de commande

int	main(int ac, char **av, char **env)
{
	// (void)ac;
	(void)av;
	if (ac == 1 && isatty(STDIN_FILENO))
	{
		routine(env);
	}
		// write(2, "minishell: stdin is not a tty", 30);
		// exit(1);
	// char *str;
	// char **tab;
	// int i = 0;
	// first_init(data);
	return (0);
	// while(strcmp("stop", str) != 0)
	// {
	// 	str = readline("minishell->");
	// }
	// tab = ft_split(str, " ");
	// free(str);
}

// probleme restant :

// no such file or directory au lieu de command not found quand on fait une commande qui existe pas
// control c apres avoir fait la commande "cat" qui r'affiche 2 fois le prompt
// probleme avec la fonction ft_get_status(cmd) elle retourne pas le bon status et on dirait qu'elle inverse les status signaux et les status normaux
// lancer le checker de l'entree standard a chaque readline
// mauvais message d'erreur pour la commande /bin/..

/*
Leaks avec ces commandes : 
- "cat" puis controle c erreur a la prochaine commande
-
*/

// probleme regle :

// proteger les write de echo pour quand on ecrit dans un fichier ou on peut plus
// leak quand il y a une erreur de parsing et qu'on fait control D
// remplacer le path de cmd par le nom seul pour imiter exactement le shell
// proteger quand y'a plus d'entrer standard


// cas a tester
/*
emoreau@made-f0Dr8s11:~/sgoinfre/minishell$ bash --posix
bash-5.1$ ..
bash: ..: command not found
bash-5.1$ ..
bash: ..: command not found
bash-5.1$ ../
bash: ../: Is a directory
bash-5.1$ /..
bash: /..: Is a directory
bash-5.1$ ..
bash: ..: command not found
bash-5.1$ < $dfgdfg
bash: $dfgdfg: ambiguous redirect
bash-5.1$ ""
bash: : command not found
bash-5.1$ exit 12 12
exit
bash: exit: too many arguments
bash-5.1$ echo $?
127
bash-5.1$ exit 12 12
exit
bash: exit: too many arguments
bash-5.1$ echo $?
1
bash-5.1$ exit 12
exit
emoreau@made-f0Dr8s11:~/sgoinfre/minishell$ exit 12 12
exit
bash: exit: too many arguments
emoreau@made-f0Dr8s11:~/sgoinfre/minishell$ bash --posix
bash-5.1$ exit pol 
exit
bash: exit: pol: numeric argument required
emoreau@made-f0Dr8s11:~/sgoinfre/minishell$ bash --posix
bash-5.1$ exit 255
exit
emoreau@made-f0Dr8s11:~/sgoinfre/minishell$ echo $?
255
emoreau@made-f0Dr8s11:~/sgoinfre/minishell$ export 98aya=dfd
bash: export: `98aya=dfd': not a valid identifier

*/

// si on se chauffe de zinzin on peut gerer le cas :
// -~