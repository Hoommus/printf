/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integerf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:43:24 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/21 19:03:14 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoxx(t_conv *conv, unsigned long long nbr)
{
	char	*new;
	size_t	len;

	new = utos_base(nbr, 16, conv->conv == 'x' ? 0 : 1);
	len = ft_strlen(new);
	new = apply_generic_precision(conv, &new, len);
	if (conv->alt_form != 0 && conv->min_width > -1 && conv->zero_padding != 0)
	{
		new = apply_generic_width(conv, &new, len);
		new = apply_alt_form_oxx(conv, &new);
	}
	else
	{
		new = apply_alt_form_oxx(conv, &new);
		new = apply_generic_width(conv, &new, len);
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
	if (conv->alt_form != 0 && conv->min_width > -1 && conv->zero_padding != 0)
	{
		new = apply_generic_width(conv, &new, len);
		new = apply_alt_form_oxx(conv, &new);
	}
	else
	{
		new = apply_alt_form_oxx(conv, &new);
		new = apply_generic_width(conv, &new, len);
	}
	return (new);
}

void	eval_di(t_conv *conv, va_list arg)
{
	long long int	d;
	size_t			len;

	if (ft_strnstr(conv->mod, "ll", 2) || conv->mod[0] == 'z')
		d = va_arg(arg, long long int);
	else if (ft_strnstr(conv->mod, "hh", 2))
		d = va_arg(arg, int);
	else if (conv->mod[0] == 'h')
		d = va_arg(arg, short);
	else if (conv->mod[0] == 'l')
		d = va_arg(arg, long);
	else if (conv->mod[0] == 't')
		d = va_arg(arg, ptrdiff_t);
	else
		d = va_arg(arg, intmax_t);
	conv->res = itos_base(d, 10);
	len = ft_strlen(conv->res);
	conv->res = apply_generic_precision(conv, &conv->res, len);
	conv->res = apply_generic_width(conv, &conv->res, len);
}

void	eval_uoxx(t_conv *conv, va_list arg)
{
	unsigned long long int	d;

	if (ft_strnstr(conv->mod, "ll", 2))
		d = va_arg(arg, unsigned long long int);
	else if (ft_strnstr(conv->mod, "hh", 2))
		d = va_arg(arg, unsigned int);
	else if (conv->mod[0] == 'h')
		d = va_arg(arg, unsigned short);
	else if (conv->mod[0] == 'l')
		d = va_arg(arg, unsigned long);
	else if (conv->mod[0] == 't')
		d = (unsigned long long int)va_arg(arg, ptrdiff_t);
	else if (conv->mod[0] == 'z')
		d = va_arg(arg, size_t);
	else
		d = va_arg(arg, uintmax_t);
	if (conv->conv == 'o')
		conv->res = itoo(conv, d);
	else if (conv->conv == 'x' || conv->conv == 'X')
		conv->res = itoxx(conv, d);
}
