/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:40:38 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/25 19:34:44 by vtarasiu         ###   ########.fr       */
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
	else if (len > conv->precision && (conv->conv == 's' || conv->conv == 'S'))
	{
		new = ft_strsub(*str, 0, (size_t)conv->precision);
		ft_strdel(str);
	}
	return (new);
}

char	*apply_generic_width(t_conv *conv, char **str, size_t len, char c)
{
	char	*new;
	char	space;
	size_t	i;

	if (conv->min_width == -1)
		return (*str);
	i = 0;
	space = (char)(c != 0 ? c : ' ');
	if (c == 0 && conv->zero_padding != 0 && conv->pad_dir != '-')
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

/*
** TODO: Привести все эти функции к одному виду (возвращать везде свап)
*/

char	*apply_alt_form_oxx(t_conv *conv, char **str)
{
	char	*swap;

	swap = *str;
	if (conv->alt_form && (conv->conv == 'x' || conv->conv == 'X'))
		if (conv->min_width != 0 && ft_strncmp(*str, "00", 2) == 0
			&& conv->precision <= 0)
		{
			(*str)[0] = '0';
			(*str)[1] = conv->conv == 'x' ? 'x' : 'X';
		}
		else
		{
			*str = ft_strjoin(conv->conv == 'x' ? "0x" : "0X", *str);
			ft_strdel(&swap);
		}
	else if (conv->alt_form && (conv->conv == 'o' || conv->conv == 'O')
							&& **str != '0')
	{
		*str = ft_strjoin("0", *str);
		ft_strdel(&swap);
	}
	return (*str);
}
