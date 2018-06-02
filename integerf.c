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

char	*trimxx(t_conv *conv, char **str)
{
	size_t	i;
	char	*swap;

	swap = *str;
	i = ft_strlen(*str);
	if (i > 8 && conv->modif < 4 && i - 8 > 0)
	{
		swap = ft_strsub(*str, i - 8, i);
		ft_strdel(str);
	}
	if (ft_strequ(swap, "00000000"))
	{
		ft_strdel(&swap);
		swap = ft_strdup("0");
	}
	return (swap);
}

char	*itoxx(t_conv *conv, unsigned long long nbr)
{
	char	*new;

	new = utos_base(nbr, 16, conv->conv == 'X' ? 1 : 0);
	if (conv->modif < 8)
		new = trimxx(conv, &new);
	new = apply_generic_precision(conv, &new, ft_strlen(new));
	if (conv->alt_form != 0 && conv->min_width > -1 && conv->zero_padding != 0)
	{
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
		new = nbr != 0 ? apply_alt_form_oxx(conv, &new) : new;
	}
	else
	{
		new = nbr != 0 || conv->conv == 'p' ? apply_alt_form_oxx(conv, &new) : new;
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
	}
	return (new);
}

char	*itoo(t_conv *conv, unsigned long long nbr)
{
	char	*new;

	new = utos_base(nbr, 8, 0);
	new = apply_generic_precision(conv, &new, ft_strlen(new));
	if (nbr != 0)
		new = apply_alt_form_oxx(conv, &new);
	if (conv->precision != -1)
		new = apply_generic_width(conv, &new, ft_strlen(new), ' ');
	else
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
	return (new);
}

char	*itou(t_conv *conv, unsigned long long nbr)
{
	char	*new;

	new = utos_base(nbr, 10, 0);
	new = apply_generic_precision(conv, &new, ft_strlen(new));
	if (nbr != 0)
		new = apply_alt_form_oxx(conv, &new);
	if (conv->precision != -1)
		new = apply_generic_width(conv, &new, ft_strlen(new), ' ');
	else
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
	return (new);
}

char	*apply_sign_or_space(t_conv *conv, char **str, int sign)
{
	char	*swap;

	swap = *str;
	if (conv->sign != 0 && *str[0] != (sign < 0 ? '-' : '+'))
	{
		swap = ft_strnew(ft_strlen(*str) + 1);
		swap[0] = (char) (sign < 0 ? '-' : '+');
		ft_strcat(swap, *str);
		ft_strdel(str);
		*str = swap;
	}
	if (conv->space != 0 && *str[0] != '-' && *str[0] != '+' && *str[0] != ' ')
	{
		swap = ft_strnew(ft_strlen(*str) + 1);
		swap[0] = ' ';
		ft_strcat(swap, *str);
		ft_strdel(str);
		*str = swap;
	}
	return (swap);
}

void	eval_di(t_conv *conv, va_list arg)
{
	long long int	d;

	if (conv->mod == 'L' || conv->mod == 'z')
		d = va_arg(arg, long long int);
	else if (conv->mod == 'H')
		d = (signed char)va_arg(arg, int);
	else if (conv->mod == 'h')
		d = (short)va_arg(arg, int);
	else if (conv->mod == 'l')
		d = va_arg(arg, long);
	else if (conv->mod == 't')
		d = va_arg(arg, ptrdiff_t);
	else if (conv->mod == 'j')
		d = va_arg(arg, intmax_t);
	else
		d = va_arg(arg, int);
	conv->res = itos_base(d, 10);
	conv->res = apply_sign_or_space(conv, &(conv->res), d);
	conv->res = apply_generic_precision(conv, &conv->res, ft_strlen(conv->res));
	conv->res = apply_generic_width(conv, &conv->res, ft_strlen(conv->res),
									conv->precision != -1 ? ' ' : 0);
}

void	eval_uoxx(t_conv *conv, va_list arg)
{
	unsigned long long int	d;

	if (conv->mod == 'L')
		d = va_arg(arg, unsigned long long int);
	else if (conv->mod == 'H')
		d = (unsigned char)va_arg(arg, unsigned int);
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
	else if (conv->conv == 'u')
		conv->res = itou(conv, d);
}

/*
** TODO: TWO FUKKEN CRUTCHES
*/

void	eval_p(t_conv *conv, va_list arg)
{
	unsigned long long	nbr;
	long long int		len;

	nbr = (unsigned long long)va_arg(arg, void *);
	conv->alt_form = '#';
	conv->conv = 'p';
	conv->mod = 'l';
	conv->modif = conv->modif | 8;
	conv->precision = -1;
	len = ft_nbrlen(nbr);
	conv->min_width = (len > conv->min_width ? len : conv->min_width) - 2;
	conv->res = itoxx(conv, nbr);
}
