/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:36:25 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/18 19:27:47 by emoreau          ###   ########.fr       */
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
	SUP_DB,
	INF,
	INF_DB,
	INFILE,
	OUTFILE,
	LIMITOR,
	PIPE,
}	t_token;

typedef enum s_quote
{
	SANS,
	SIMPLE,
	DOUBLE,
}	t_quote;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	t_quote			quote;
	// int				i;
	// t_data		*data;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_data
{
	char	*str;
	// char 	*quote;
	char 	**tab;
	int		nb_word;
	t_lexer	*lexer;
}	t_data;

int		routine(char **env);
t_data	*data_init(void);
int		quote(char *str);
int		find_dbquote(char *str, int *i);
int		find_quote(char *str, int *i);

// lexer

int	is_separator(char c);
int	is_space(char c);
int	is_quote(char c);
int	separator_len(char *str, int i);
char	*find_sep(char *str, int *i);
int	quote_len(char *str, int i, char c);
char *quote_word(char *str, int *i, char c);
// int	dquote_len(char *str, int i);
char *dquote_word(char *str, int *i);
int	word_len(char *str, int i);
char *normal_word(char *str, int *i);
char	*find_word(char *str, int *i);
char *find_token(t_data *data, int *i);
t_lexer	*create_node(t_data *data, int *i);
t_lexer	*lst_cmd(t_data *data);
t_lexer	*lexer(t_data *data);
t_lexer	*ft_lexer(t_data *data);
int tokend(char *str, int i);
int stop_token(char c);



#endif

// int	pars_separator(t_data *data);