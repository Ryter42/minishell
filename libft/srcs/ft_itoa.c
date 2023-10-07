/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:07:27 by emoreau           #+#    #+#             */
/*   Updated: 2022/11/24 12:19:13 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	lent(long long n)
{
	int	i;

	i = 1;
	while (n > 9 || n < -9)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*convert(long long no, int i)
{
	char	*nb;

	nb = malloc(sizeof(char) * (i + 1));
	if (!nb)
		return (NULL);
	nb[i] = 0;
	i--;
	while (no > 9)
	{
		nb[i] = no % 10 + '0';
		no = no / 10;
		i--;
	}
	nb[i] = no + '0';
	return (nb);
}

char	*ft_itoa(int n)
{
	int			i;
	int			s;
	long long	no;
	char		*nb;

	no = n;
	i = lent(no);
	if (no < 0)
	{
		s = 1;
		no = -no;
	}
	else
		s = 0;
	i = i + s;
	nb = convert(no, i);
	if (s == 1)
		nb[0] = '-';
	return (nb);
}
