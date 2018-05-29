/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integerf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:43:24 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/25 19:12:32 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoxx(t_conv *conv, unsigned long long nbr)
{
	char	*new;
	size_t	len;

	new = utos_base(nbr, 16, conv->conv == 'x' ? 0 : 1);
	if (nbr == 0)
	{
		ft_strdel(&new);
		new = ft_strnew(1);
		new[0] = '0';
	}
	len = ft_strlen(new);
	new = apply_generic_precision(conv, &new, len);
	if (conv->alt_form != 0 && conv->min_width > -1 && conv->zero_padding != 0)
	{
		new = apply_generic_width(conv, &new, len, 0);
		new = nbr != 0 ? apply_alt_form_oxx(conv, &new) : new;
	}
	else
	{
		new = nbr != 0 ? apply_alt_form_oxx(conv, &new) : new;
		new = apply_generic_width(conv, &new, len, 0);
	}
	return (new);
}

char	*itoo(t_conv *conv, unsigned long long nbr)
{
	char	*new;
	size_t	len;

	new = utos_base(nbr, 8, 0);
	len = ft_strlen(new);
	new = apply_generic_precision(conv, &new, len);
	new = apply_alt_form_oxx(conv, &new);
	if (conv->precision != -1)
		new = apply_generic_width(conv, &new, ft_strlen(new), ' ');
	else
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
	return (new);
}

void	eval_di(t_conv *conv, va_list arg)
{
	long long int	d;
	size_t			len;

	if (conv->mod == 'L' || conv->mod == 'z')
		d = va_arg(arg, long long int);
	else if (conv->mod == 'H')
		d = va_arg(arg, int);
	else if (conv->mod == 'h')
		d = (short)va_arg(arg, int);
	else if (conv->mod == 'l')
		d = va_arg(arg, long);
	else if (conv->mod == 't')
		d = va_arg(arg, ptrdiff_t);
	else
		d = va_arg(arg, intmax_t);
	conv->res = itos_base(d, 10);
	len = ft_strlen(conv->res);
	conv->res = apply_generic_precision(conv, &conv->res, len);
	conv->res = apply_generic_width(conv, &conv->res, len, 0);
}

void	eval_uoxx(t_conv *conv, va_list arg)
{
	unsigned long long int	d;

	if (conv->mod == 'L')
		d = va_arg(arg, unsigned long long int);
	else if (conv->mod == 'H')
		d = va_arg(arg, unsigned int);
	else if (conv->mod == 'h')
		d = (unsigned short)va_arg(arg, unsigned int);
	else if (conv->mod == 'l')
		d = va_arg(arg, unsigned long);
	else if (conv->mod == 't')
		d = (unsigned long long int)va_arg(arg, ptrdiff_t);
	else if (conv->mod == 'z')
		d = va_arg(arg, size_t);
	else
		d = va_arg(arg, uintmax_t);
	if (conv->conv == 'o')
		conv->res = itoo(conv, d);
	else if (conv->conv == 'x' || conv->conv == 'X')
		conv->res = itoxx(conv, d);
}

void	eval_p(t_conv *conv, va_list arg)
{
	unsigned long long	nbr;
	char				*new;
	long long int		len;

	nbr = (unsigned long long)va_arg(arg, void *);
	conv->alt_form = '#';
	conv->conv = 'x';
	conv->precision = -1;
/*
** TODO: FUKKEN CRUTCH
*/
	len = ft_nbrlen(nbr);
	conv->min_width = (len > conv->min_width ? len : conv->min_width) - 2;
	conv->res = itoxx(conv, nbr);
}
