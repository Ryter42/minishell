/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:59:01 by emoreau           #+#    #+#             */
/*   Updated: 2023/01/25 11:04:15 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putcharlen(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstrlen(char *s)
{
	int		i;

	i = 0;
	if (s)
	{
		while (*s)
		{
			write(1, s, 1);
			s++;
			i++;
		}
	}
	else
	{
		write(1, "(null)", 6);
		return (6);
	}
	return (i);
}

int	printarg(va_list arg, char c, int *len)
{
	if (c == 'c')
		*len += ft_putcharlen(va_arg(arg, int));
	if (c == 's')
		*len += ft_putstrlen(va_arg(arg, char *));
	if (c == 'p')
		*len = ft_pointeur(va_arg(arg, void *), len);
	if (c == 'i' || c == 'd')
		*len = ft_putnbr(va_arg(arg, int), len);
	if (c == 'u')
			*len = baselen(va_arg(arg, unsigned int), "0123456789", len);
	if (c == 'x')
		*len = baselen(va_arg(arg, unsigned int), "0123456789abcdef", len);
	if (c == 'X')
		*len = baselen(va_arg(arg, unsigned int), "0123456789ABCDEF", len);
	if (c == '%')
		*len += ft_putcharlen('%');
	return (*len);
}
