/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:04:40 by emoreau           #+#    #+#             */
/*   Updated: 2023/01/25 11:39:20 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	arg;

	va_start(arg, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			len = printarg(arg, *format, &len);
		}
		else
		{
			write(1, format, 1);
			len++;
		}
		format++;
	}
	va_end(arg);
	return (len);
}
