/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 02:15:25 by emoreau           #+#    #+#             */
/*   Updated: 2023/01/25 11:05:50 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

unsigned long	verif(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] < 32)
			return (1);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (i);
}

int	baselen(unsigned long nb, char *base, int *i)
{
	if (verif(base) <= 1)
		return (0);
	(*i)++;
	if (nb < verif(base))
	{
		ft_putcharlen(base[nb]);
	}
	if (nb >= verif(base))
	{
		baselen(nb / verif(base), base, i);
		ft_putcharlen(base[nb % verif(base)]);
	}
	return (*i);
}

int	ft_pointeur(void *adresse, int *len)
{
	unsigned long	n;

	n = (unsigned long)adresse;
	if (adresse == NULL)
	{
		write(1, "(nil)", 5);
		return (*len + 5);
	}
	write (1, "0x", 2);
	return (baselen(n, "0123456789abcdef", len) + 2);
}

int	printnum(int nb, int *i)
{
	(*i)++;
	if (nb > 9)
		printnum (nb / 10, i);
	ft_putcharlen (48 + nb % 10);
	return (*i);
}

int	ft_putnbr(int n, int *i)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11 + *i);
	}
	if (n < 0)
	{
		ft_putcharlen('-');
		n = -n;
		(*i)++;
	}
	return (printnum(n, i));
}
