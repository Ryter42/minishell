/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:36:25 by emoreau           #+#    #+#             */
/*   Updated: 2023/11/13 16:04:02 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
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

// typedef enum s_quote
// {
// 	SANS,
// 	SIMPLE,
// 	DOUBLE,
// }	t_quote;

typedef struct s_data
{
	char	*str;
	char 	**env;
	char 	**path;
	int		fd[2];
	int		nb_cmd;
	int		fd_tmp;
	pid_t	*pid;
	// int		nb_loop;
	// char 	*quote;
	// char 	**tab;
	// int		nb_word;
	// t_lexer	*lexer;
	// t_cmd	*cmd;
}	t_data;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	// t_quote			quote;
	// int				i;
	// t_data		*data;
	t_data			*data;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_cmd
{
	char			*cmd;
	int				bultin;
	char			**arg;
	char 			*infile;
	char 			*outfile;
	int				add_out;
	int				heredoc;
	char			**limiter;
	t_data			*data;
	struct s_cmd	*next;
	// struct s_cmd	*prev;
}	t_cmd;


int		routine(char **env);
t_data	*data_init(char **env);
int		quote_verif(char *str);
int		find_dbquote(char *str, int *i);
int		find_quote(char *str, int *i);
char	**cpy_env_with(char **env, char *arg);
void	set_signal_action(void);

// lexer

int	is_separator(char c);
int	is_space(char c);
int	is_quote(char c);
int	is_redir(char c);

int		separator_len(char *str, int i);
char	*find_sep(char *str, int *i);
int		quote_len(char *str, int i, char c);
char 	*quote_word(char *str, int *i, char c);
// char *dquote_word(char *str, int *i);
int		word_len(char *str, int i);
char 	*normal_word(char *str, int *i);
char	*find_word(char *str, int *i);
char 	*find_token(t_data *data, int *i);
t_lexer	*create_node(t_data *data, int *i);
t_lexer	*lst_lexer(t_data *data);
t_cmd	*lexer(t_data *data);
int 	tokend(char *str, int i);
int 	stop_token(char c);

// check

int first_check(char *str);
int	metachar_verif(char *str);
int	metachar_verif2(char *str);
int	metachar_verif3(int i, char *str);
int	is_metachar(char c);
int check(t_lexer *lexer);
int	check_separator(t_lexer *lexer);

// token

void	give_token(t_lexer *lexer);
t_token	token_inf(char *str);
t_token	token_sup(char *str);
t_token	token_sep(t_lexer *lexer);

// clean
t_cmd	*clean_cmd(t_lexer *lexer);
t_cmd	*lst_cmd(t_lexer *lexer);
t_cmd	*create_cmd(t_lexer *lexer);
void	outfile(t_lexer *lexer, t_cmd *cmd);
void	create_outfile(t_lexer *lexer);
char	*infile(t_lexer *lexer);
char	**arg(t_lexer *lexer, char *cmd);
int		nb_arg(t_lexer *lexer);
char	*commande(t_lexer *lexer);
char	**limiter(t_lexer *lexer, int n);
int		nb_heredoc(t_lexer *lexer);

int		num_quote(char *str);
int		copy_in_quote(char *str, char *str2, int *i, int *i2);
char	*line_without_quote(char *str);
void	rm_quote(t_lexer *lexer);


// expand
t_lexer	*expand(t_lexer *lexer, char **env);
void	variable(t_lexer *lexer, char **env);
void	replace_var(char **env, t_lexer *lexer, char *var_name);
char	*find_var(char **env, char *name, int len);
int 	bt_sp_quote(char *str, int i);
char	*find_var_name(char *str, int index);
int		variable_len(char *str, int i);

// pipex

void	ft_heredoc(t_cmd *cmd);
int		execution(t_cmd *cmd);
t_data	*init(int ac, char **av, char **env);
void	loopfork(t_cmd *cmd);
void	get_cmd(t_data *data);
void	firstcmd(t_data *data);
void	midlecmd(t_data *data);
void	lastcmd(t_data *data);
void	exec(t_cmd *cmd, int index);
char	*pathenv(char **env);
int		is_there_slash(char *str);
char	**addslash(char **env);
int		findpath(t_data *data, char *cmd);
// int		is_heredoc(void);
void	heredoc(char *limiter, int fd);
int		ft_open(t_data *data);
int		ft_open_heredoc(void);
void	fork_heredoc(t_cmd *cmd);
void	ft_wait(t_cmd *cmd);
void	dup_infile(t_cmd *cmd, int index);
void	dup_outfile(t_cmd *cmd);


void	print_cmd(t_cmd *cmd);
// bultin
int		is_bultin(char *cmd);
void	exec_fork_bultin(t_cmd *cmd, int index);
void	exec_env_bultin(t_cmd *cmd, int index);
void	echo(t_cmd *cmd);
void	pwd(t_cmd *cmd);
void	unset(t_cmd *cmd);
void	env(t_cmd *cmd);
void	export(t_cmd *cmd);
void	cd(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);

// free
void	free_all(t_cmd *cmd);
void	free_cmd(t_cmd *cmd);
void	free_data(t_data *data);
void	free_tab(char **tab);
void	free_tab(char **tab);
void	free_lexer(t_lexer *lexer);



#endif

// essauer allecw joue de ls misiai
// essauer sleds joue de ls misoaie pop
// int	pars_separator(t_data *data);