/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:35:08 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/07 20:30:02 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void parsing(char *str)
// {
// 	t_cmd cmd;
	
// }

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *str;
	char **tab;
	int i = 0;
	
	str = readline("minishell ");
	// while(strcmp("stop", str) != 0)
	// {
	// 	parsing(str);
	// 	str = readline("minishell->");
	// }
	tab = ft_split(str, " |<>");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
