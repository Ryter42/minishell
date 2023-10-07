/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:52:47 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/18 10:24:46 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nb)
{
	int		i;
	int		s;
	int		nbr;
	char	*n;

	n = (char *)nb;
	nbr = 0;
	s = 1;
	i = 0;
	while ((n[i] > 6 && n[i] < 14) || n[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			s = -s;
		i++;
	}
	while (nb[i] > 47 && nb[i] < 58)
	{
		nbr = nbr * 10 + nb[i] - 48;
		i++;
	}
	return (nbr * s);
}
