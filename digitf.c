/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:43:24 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/20 17:46:53 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_generic_precision(t_conv *conv, char **str, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	new = *str;
	if ((long long)len <= conv->precision && ft_strchr(NUMERIC, conv->conv))
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

	if (conv->min_width == -1)
		return (*str);
	i = 0;
	space = ' ';
	if (conv->zero_padding != 0 && ft_strchr(NUMERIC_EXT, conv->conv) != NULL
		&& conv->precision < 0 && conv->pad_dir != '-')
		space = '0';
	new = ft_strnew((size_t)conv->min_width);
	while (conv->pad_dir != '-' && i < conv->min_width - len)
		new[i++] = space;
	ft_strcat(new, *str);
	i = len;
	while (conv->pad_dir == '-' && i < conv->min_width)
		new[i++] = space;
	ft_strdel(str);
	return (new);
}

char	*apply_alt_form_oxx(t_conv *conv, char **str)
{
	char	*swap;

	if (conv->conv == 'x' || conv->conv == 'X')
		if (conv->min_width != 0 && ft_strncmp(*str, "00", 2) == 0
			&& conv->precision == 0)
		{
			(*str)[0] = '0';
			(*str)[1] = conv->conv == 'x' ? 'x' : 'X';
		}
		else
		{
			swap = *str;
			*str = ft_strjoin(conv->conv == 'x' ? "0x" : "0X", *str);
			ft_strdel(&swap);
		}
	else if ((conv->conv == 'o' || conv->conv == 'O') && (*str)[0] != '0')
	{
		swap = *str;
		*str = ft_strjoin("0", *str);
		ft_strdel(&swap);
	}
	return (*str);
}

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
	char *new;
	size_t len;

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
