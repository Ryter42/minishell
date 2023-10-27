/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:43:37 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/27 04:11:09 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	get_cmd(t_data *data)
// {
// 	data->arg = ft_split(data->av[data->index], ' ');
// 	if (is_there_slash(data->av[data->index]) == 0)
// 	{
// 		data->file = findpath(data->path, data->arg[0], data);
// 		data->cmd = ft_strjoin(data->path[data->file], data->arg[0]);
// 	}
// 	else
// 		data->cmd = ft_strdup(data->av[data->index]);
// }

// void	firstcmd(t_data *data)
// {
// 	int	fd;

// 	fd = ft_open(data);
// 	close(data->fd[0]);
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		perror("redir in");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 	{
// 		perror("redir out");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (execve(data->cmd, data->arg, data->env) == -1)
// 	{
// 		perror(data->cmd);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	midlecmd(t_data *data)
// {
// 	close(data->fd[0]);
// 	if (dup2(data->fd_tmp, STDIN_FILENO) == -1)
// 	{
// 		perror("redir in");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 	{
// 		perror("redir out");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (execve(data->cmd, data->arg, data->env) == -1)
// 	{
// 		perror("data->cmd");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	lastcmd(t_data *data)
// {
// 	int	fd;

// 	if (data->heredoc)
// 		fd = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		fd = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	close(data->fd[1]);
// 	if (dup2(data->fd_tmp, STDIN_FILENO) == -1)
// 	{
// 		perror("redir in");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("redir out");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (execve(data->cmd, data->arg, data->env) == -1)
// 	{
// 		perror(data->cmd);
// 		exit(EXIT_FAILURE);
// 	}
// }

int	open_infile(t_cmd *cmd,int index)
{
	int	fd;

	// dprintf(2, "---dans infile----\n		cmd = %s	infile = %s	index = %d\n", cmd->cmd, cmd->infile,index);
	if (cmd->infile)
	{
		// dprintf(2, "infile = %s\n\n", cmd->infile);
		fd = open(cmd->infile, O_RDONLY);
		if (index)
			close(cmd->data->fd_tmp);
		// dprintf(2, "fd in == %d\n\n", fd);		
	}
	else if (cmd->heredoc)
	{
		// dprintf(2, "heredoc = %d\n\n", cmd->heredoc);
		fd = open(".heredoc_tmp", O_RDONLY);
		if (index)
			close(cmd->data->fd_tmp);
		// dprintf(2, "fd in == %d\n\n", fd);		
	}
	else if (index)
	{
		// dprintf(2, "pipe numero %d\n\n", index);
		fd = cmd->data->fd_tmp;
		// dprintf(2, "fd in == %d\n\n", fd);
	}
	else
	{
		// dprintf(2, "rien_in\n\n");	
		// dprintf(2, "fd_tmp == %d\n", cmd->data->fd_tmp );
		// close(cmd->data->fd_tmp);
		return (0);
	}
	if (fd == -1)
	{
		close(cmd->data->fd[0]);
		close(cmd->data->fd[1]);
		perror(cmd->infile);
		// ft_free(cmd);
		exit(EXIT_FAILURE);
	}
	return (fd);
}


void	dup_infile(t_cmd *cmd, int index)
{
	int	fd;
	
	close(cmd->data->fd[0]); 
	fd = open_infile(cmd, index);
	// if (!index)
	// 	close(cmd->data->fd_tmp);
	// dprintf(2, "2-fd in == %d\n\n", fd);
	if (fd)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("redir in");
			close(fd);
			exit (EXIT_FAILURE);
		}
		close(fd);
	}
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;

// 	char cwd[1024];
// if (getcwd(cwd, sizeof(cwd)) != NULL) {
//     printf("Répertoire actuel : %s\n", cwd);
// } else {
//     perror("Erreur lors de la récupération du répertoire actuel");
//     return -1; // ou une autre gestion d'erreur
// }

//  #include <sys/stat.h>

// struct stat {
//     dev_t         st_dev;      /* ID du périphérique contenant le fichier */
//     ino_t         st_ino;      /* Numéro d'inœud */
//     mode_t        st_mode;     /* Mode du fichier (permissions et type) */
//     nlink_t       st_nlink;    /* Nombre de liens matériels */
//     uid_t         st_uid;      /* ID de l'utilisateur propriétaire */
//     gid_t         st_gid;      /* ID du groupe propriétaire */
//     dev_t         st_rdev;     /* ID du périphérique (si fichier spécial) */
//     off_t         st_size;     /* Taille totale en octets */
//     blksize_t     st_blksize;  /* Taille du bloc d'E/S optimal pour le système de fichiers */
//     blkcnt_t      st_blocks;   /* Nombre de blocs alloués */
//     struct timespec st_atim;  /* Heure d'accès */
//     struct timespec st_mtim;  /* Heure de modification */
//     struct timespec st_ctim;  /* Heure de changement de statut */
// };

// struct stat st;
// if (stat(".", &st) == 0) {
//     printf("Permissions du répertoire actuel : %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
// } else {
//     perror("Erreur lors de la récupération des permissions du répertoire actuel");
//     return -1; // ou une autre gestion d'erreur
// }


	// dprintf(2, "---dans outfile---\n		cmd = %s	outfile = %s	cmd->next = %p\n", cmd->cmd, cmd->outfile, cmd->next);
		// dprintf(2, "outfile =  %s\n\n", cmd->outfile);
	if (cmd->outfile)
	{
		if (cmd->add_out)
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			// dprintf(2, "fd out == %d\n\n", fd);
		}
		else
		{
			// dprintf(2, "outfile == %s\n\n", cmd->outfile);
			fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			// fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			// dprintf(2, "fd out == %d\n\n", fd);
			// fd = open("elias", O_WRONLY | O_TRUNC | O_CREAT, 0644);
			// dprintf(2, "fd out == %d\n\n", fd);
		}
		close(cmd->data->fd[1]);
	}
	else if (cmd->next)
	{
		// dprintf(2, "cmd->next =  %p\n\n", cmd->next);
		fd = cmd->data->fd[1];
		// dprintf(2, "fd out == %d\n\n", fd);
	}
	else
	{
		// dprintf(2, "rien_out\n\n");
		close(cmd->data->fd[1]);
		return (0);
	}
	if (fd == -1)
	{
		close(cmd->data->fd[0]);
		close(cmd->data->fd[1]);
		perror(cmd->outfile);
		// ft_free(cmd);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	dup_outfile(t_cmd *cmd)
{
	int	fd;
	
	fd = open_outfile(cmd);
	// dprintf(2, "cmd == %s 2-fd out == %d\n\n",cmd->cmd, fd);
	// dprintf(2, "2-fd out == %d\n\n", fd);
	if (fd)
	{
		// dprintf(2, "fd = %d\n", fd);
		// close(cmd->data->fd[0]);
		if (dup2(fd, STDOUT_FILENO) == - 1)
		{
			perror("redir out");
			close(fd);
			exit (EXIT_FAILURE);
		}
		close(fd);
	}
	// else
	// 	dprintf(2, "fd = 0\n");
}

void	printab(char **tab, char *var)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s ", var);
		printf("%d = %s	", (i + 1), tab[i]);
		i++;
	}
	printf("\n");
}

void	print_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		printf("cmd = %s\n", cmd->cmd);
	if (cmd->infile)
		printf("infile = %s\n", cmd->infile);
	if (cmd->heredoc)
		printf("heredoc = %d\n", cmd->heredoc);
	if (cmd->limiter)
			printab(cmd->limiter, "limiter");
	if (cmd->arg)
		printab(cmd->arg, "arg");
	if (cmd->outfile)
		printf("outfile = %s\n", cmd->outfile);
	if (cmd->add_out)
		printf("add = %d\n", cmd->add_out);
}

void	exec(t_cmd *cmd, int index)
{
	// (void)index;
	// print_cmd(cmd);
	dup_infile(cmd, index);
	dup_outfile(cmd);
	if (!cmd->cmd)
		exit(EXIT_SUCCESS);
	if (execve(cmd->cmd, cmd->arg, cmd->data->env) == -1)
	{
		perror(cmd->cmd);
		exit(EXIT_FAILURE);
	}
}
