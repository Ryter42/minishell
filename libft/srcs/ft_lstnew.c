/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:09:27 by emoreau           #+#    #+#             */
/*   Updated: 2023/07/04 13:39:58 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlist;

	newlist = malloc(sizeof(t_list));
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}

t_list	*lstnewint(int content)
{
	t_list	*newlist;

	newlist = malloc(sizeof(t_list));
	newlist->value = content;
	newlist->next = NULL;
	return (newlist);
}
