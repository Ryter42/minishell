/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:29:03 by emoreau           #+#    #+#             */
/*   Updated: 2023/10/22 02:01:04 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	is_separator(char c)
{
	if (is_redir(c) == 1 || c == '|')
		return (1);
	else
		return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '	')
		return (1);
	else
		return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	else
		return (0);
}

int stop_token(char c)
{
	if (c == 0 || is_space(c) == 1 || is_separator(c) == 1)
		return (1);
	else
		return (0);
}