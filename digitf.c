/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:43:24 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/15 12:22:54 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	nbr_len(long long int nbr, int base)
{
	size_t	i;

	i = nbr < 0 && base == 10 ? 1 : 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

char	*nbr_to_str(long long int nbr, int base)
{
	size_t	len;
	char	*str;

	len = nbr_len(nbr, base);
	str = ft_strnew(len);
	if (base == 10 && nbr < 0)
		str[0] = '-';
	if (nbr == 0)
		str[0] = '0';
	str[len] = '\0';
	while (nbr)
	{
		str[len--] = ITOA_DIGITS[ABS(nbr % base)];
		nbr /= base;
	}
	return (str);
}

void	eval_di(t_conv *conv, va_list arg)
{
	long long int d;

	if (ft_strnstr(conv->mod, "ll", 2) || conv->mod[0] == 'z')
		d = va_arg(arg, long long int);
	else if (ft_strnstr(conv->mod, "hh", 2))
		d = va_arg(arg, signed char);
	else if (conv->mod[0] == 'h')
		d = va_arg(arg, short);
	else if (conv->mod[0] == 'l')
		d = va_arg(arg, long);
	else if (conv->mod[0] == 't')
		d = va_arg(arg, ptrdiff_t);
	else if (conv->mod[0] == 'j')
		d = va_arg(arg, intmax_t);
	else
		d = va_arg(arg, intmax_t);
	conv->res = nbr_to_str(d, 10);
}