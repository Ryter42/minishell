/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:36:25 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/15 02:10:06 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_token
{
	CMD,
	ARG,
	SUP,
	SUP_DBE,
	INF,
	INF_DBE,
	FD,
	LIMITOR,
	PIPE,
}	t_token;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	// int				i;
	// t_data		*data;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_data
{
	char	*str;
	char 	*quote;
	char 	**tab;
	int		nb_word;
	t_lexer	*lexer;
}	t_data;

#endif
