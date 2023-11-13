/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 03:11:58 by elias             #+#    #+#             */
/*   Updated: 2023/10/30 17:37:52 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	variable_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != '"' && str[i] != '$')
	{
		i++;
		len++;
	}
	return (len);
}

char	*find_var_name(char *str, int index)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (variable_len(str, index) + 1));
	while (str[index] && str[index] != '"' && str[index] != '$')
	{
		res[i] = str[index];
		index++;
		i++;
	}
	res[i] = 0;
	return (res);
}

int bt_sp_quote(char *str, int i)
{
	int		index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\'')
		{
			index++;
			find_quote(str, &index);
			if (index > i)
				return (1);
		}
		if (str[index] == '"')
		{
			index++;
			find_dbquote(str, &index);
			if (index > i)
				return (0);
		}
		if (index == i)
			return (0);
		index++;
	}
	return (0);
}

char	*find_var(char **env, char *name, int len)
{
	int	i;
	int	index;
	char *res;

	i = 0;
	index = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			break ;
		i++;
	}
	if (env[i])
	{
		res = malloc(sizeof(char) * (ft_strlen(env[i]) - len));
		while (env[i][index + len + 1])
		{
			res[index] = env[i][index + len + 1];
			index++;
		}
		res[index] = 0;
		return (res);
	}
	else
		return (NULL);
}
