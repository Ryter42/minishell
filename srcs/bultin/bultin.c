/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:27:42 by elias             #+#    #+#             */
/*   Updated: 2023/11/22 19:58:36 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_bultin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
		return (1);
	return (0);
}

int	is_env_bultin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
		return (1);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0 && ft_strlen(cmd->cmd) == 6)
		return (1);
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0 && ft_strlen(cmd->cmd) == 5)
		return (1);
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		return (1);
	else
		return (0);
}

void	exec_env_bultin(t_cmd *cmd, int index)
{
	// printf("address de data dans exec_env = %p\n", cmd->data);
	// if (cmd->limiter)
	// 	ft_heredoc(cmd);
	dup_infile(cmd, index);
	dup_outfile(cmd);
	// (void)index;
	// ft_redir(cmd, index);
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
		cd(cmd);
	if (ft_strncmp(cmd->cmd, "export", 6) == 0 && ft_strlen(cmd->cmd) == 6)
		export(cmd);
	if (ft_strncmp(cmd->cmd, "unset", 5) == 0 && ft_strlen(cmd->cmd) == 5)
		unset(cmd);
	if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
	{
		ft_exit(cmd);
	}
	// reset_in_out(cmd);

}

int	is_fork_bultin(t_cmd *cmd, int index)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		return (1);
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		return (1);
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		return (1);
	// printf("address de cmd_next dans bultin = %p\n", cmd->next);
	if (cmd->next || index)
	{
		if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
			return (1);
		if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
			return (1);
		if (ft_strncmp(cmd->cmd, "export", 6) == 0 && ft_strlen(cmd->cmd) == 6)
			return (1);
		if (ft_strncmp(cmd->cmd, "unset", 5) == 0 && ft_strlen(cmd->cmd) == 5)
			return (1);
	}
	return (0);
}

void	exec_fork_bultin(t_cmd *cmd, int index)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		echo(cmd);
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		pwd(cmd);
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		env(cmd);
	if (cmd->next || index)
	{
		// dprintf(2, "cmd->next = %p et index = %d\n", cmd->next, index);
		if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
			ft_exit(cmd);
		if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
			cd(cmd);
		if (ft_strncmp(cmd->cmd, "export", 6) == 0 && ft_strlen(cmd->cmd) == 6)
			export(cmd);
		if (ft_strncmp(cmd->cmd, "unset", 5) == 0 && ft_strlen(cmd->cmd) == 5)
			unset(cmd);
	}
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	str1 = (unsigned char *) s1;
// 	str2 = (unsigned char *) s2;
// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (str1[i] == str2[i] && i < n - 1 && (str1[i] && str2[i]))
// 		i++;
// 	return (str1[i] - str2[i]);
// }
