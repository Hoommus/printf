/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:43:24 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/18 19:59:07 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_generic_precision(t_conv *conv, char **str, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	new = *str;
	if (len < conv->precision && ft_strchr(NUMERIC, conv->conv))
	{
		new = ft_strnew((size_t)conv->precision);
		while (i < conv->precision - len)
			new[i++] = '0';
		ft_strcat(new, *str);
		ft_strdel(str);
	}
	else if (len > conv->precision && conv->conv == 's' || conv->conv == 'S')
	{
		new = ft_strsub(*str, 0, (size_t)conv->precision);
		ft_strdel(str);
	}
	return (new);
}

char	*apply_generic_width(t_conv *conv, char **str, size_t len)
{
	char	*new;
	char	space;
	size_t	i;

	i = 0;
	new = *str;
	space = ' ';
	if (conv->zero_padding != 0 && ft_strchr(NUMERIC_EXT, conv->conv) != NULL
		&& conv->precision < 0)
		space = '0';
	if (len < conv->min_width)
	{
		new = ft_strnew((size_t)conv->min_width);
		while (i < conv->min_width - len)
			new[i++] = space;
		ft_strcat(new, *str);
		ft_strdel(str);
	}
	else if (len > conv->precision && conv->conv == 's' || conv->conv == 'S')
	{
		new = ft_strsub(*str, 0, (size_t)conv->precision);
		ft_strdel(str);
	}
	return (new);
}

char	*itoxx(t_conv *conv, unsigned long long nbr)
{
	char *new;
	char *swap;
	size_t len;

	new = utos_base(nbr, 16, conv->conv == 'x' ? 0 : 1);
	len = ft_strlen(new);
	new = apply_generic_precision(conv, &new, len);
	if (conv->precision >= 0 && conv->alt_form != 0)
	{
		swap = ft_strjoin(conv->conv == 'x' ? "0x" : "0X", new);
		free(new);
		new = swap;
	}
	else if (conv->min_width >= 0)
	{

	}
	return (new);
}

void	eval_di(t_conv *conv, va_list arg)
{
	long long int	d;

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
//	else if (conv->mod[0] == 'j')
//		d = va_arg(arg, intmax_t);
	else
		d = va_arg(arg, intmax_t);
	conv->res = itos_base(d, 10);
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
//	else if (conv->mod[0] == 'j')
//		d = va_arg(arg, uintmax_t);
	else
		d = va_arg(arg, uintmax_t);
	if (conv->conv == 'o')
		conv->res = utos_base(d, 8, 0);
	else if (conv->conv == 'x' || conv->conv == 'X')
		conv->res = itoxx(conv, d);
}
