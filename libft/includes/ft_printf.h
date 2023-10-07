/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:09:14 by emoreau           #+#    #+#             */
/*   Updated: 2023/01/25 11:25:02 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int				ft_printf(const char *format, ...);
int				ft_putcharlen(char c);
int				ft_putstrlen(char *s);
int				printarg(va_list arg, char c, int *len);
unsigned long	verif(char *base);
int				baselen(unsigned long nbr, char *base, int *i);
int				ft_pointeur(void *adresse, int *len);
int				ft_putnbr(int n, int *i);

#endif