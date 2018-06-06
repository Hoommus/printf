/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:40:38 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/06/06 20:35:04 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_generic_precision(t_conv *conv, char **str, size_t len)
{
	char	*swap;
	size_t	i;

	i = 0;
	swap = *str;
	if ((long long)len <= conv->precision && ft_strchr(NUMERIC, conv->conv))
	{
		swap = ft_strnew((size_t)conv->precision);
		while (i < conv->precision - len)
			swap[i++] = '0';
		ft_strcat(swap, *str);
		ft_strdel(str);
	}
	else if (((long long)len) > conv->precision && conv->precision != -1
				&& (conv->conv == 's' || conv->conv == 'S'))
	{
		swap = ft_strsub(*str, 0, conv->precision < 0 ? ft_strlen(*str)
													: (size_t)conv->precision);
		ft_strdel(str);
	}
	return (swap);
}

char	*apply_generic_width(t_conv *conv, char **str, size_t len, char c)
{
	char	*swap;
	char	space;
	long	i;

	if (conv->min_width == -1)
		return (*str);
	i = 0;
	space = (char)(c != 0 ? c : ' ');
	if (c == 0 && conv->zero_padding != 0 && conv->pad_dir != '-')
		space = '0';
	swap = ft_strnew((size_t)conv->min_width);
	while (conv->pad_dir != '-' && i < conv->min_width - (long)len)
		swap[i++] = space;
	ft_strcat(swap, *str);
	i = len;
	while (conv->pad_dir == '-' && i < conv->min_width)
		swap[i++] = space;
	ft_strdel(str);
	return (swap);
}

/*
** TODO: Привести все эти функции к одному виду (возвращать везде свап)
*/

char	*apply_alt_form_oxx(t_conv *conv, char **str)
{
	char	*swap;

	swap = *str;
	if (conv->alt_form &&
		(conv->conv == 'x' || conv->conv == 'X' || conv->conv == 'p'))
		if (conv->min_width != 0 && ft_strncmp(*str, "00", 2) == 0
			&& conv->precision <= 0)
		{
			(*str)[0] = '0';
			(*str)[1] = conv->conv == 'X' ? 'X' : 'x';
		}
		else
		{
			*str = ft_strjoin(conv->conv == 'X' ? "0X" : "0x", *str);
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

char	*apply_sign_or_space(t_conv *conv, char **str, int sign)
{
	char	*swap;

	swap = *str;
	if (conv->sign != 0 && *str[0] != (sign < 0 ? '-' : '+'))
	{
		if (swap[0] == '0')
			swap[0] = sign < 0 ? '-' : '+';
		else
		{
			swap = ft_strjoin(sign < 0 ? "-" : "+", swap);
			ft_strdel(str);
		}
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
