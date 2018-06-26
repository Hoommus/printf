/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:35:00 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/06/19 14:57:56 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_unicode_precision(t_conv *conv, char **str)
{
	char	*swap;
	size_t	i;

	if (conv->precision < 0)
		return (*str);
	swap = *str;
	i = conv->precision;
	while (swap[i] != '\0' && swap[i] & 0x80
			&& !((swap[i] & 0xC0) == 192
				|| (swap[i] & 0xE0) == 224
				|| (swap[i] & 0xF0) == 240))
	{
		i--;
	}
	if (conv->precision == 0 && conv->conv == 'c')
		i = 1;
	if (conv->precision >= 0)
	{
		swap = ft_strsub(swap, 0, i);
		ft_strdel(str);
	}
	return (swap);
}

void	eval_cs(t_conv *conv, va_list *arg)
{
	char	*str;
	char	*ar;

	if (conv->conv == 's')
	{
		if (conv->modif & 4 || conv->modif & 8)
			str = to_unicode_string(va_arg(*arg, wchar_t *));
		else
		{
			ar = va_arg(*arg, char *);
			str = ar == NULL ? ft_strdup("(null)") : ft_strdup(ar);
		}
	}
	else
	{
		if (conv->modif & 4 || conv->modif & 8)
			str = to_unicode((wchar_t)va_arg(*arg, long));
		else
			str = to_unicode((char)va_arg(*arg, int));
	}
	if (str == NULL)
		str = ft_strdup("(null)");
	str = apply_unicode_precision(conv, &str);
	str = apply_generic_width(conv, &str, ft_strlen(str), 0);
	conv->res = str;
}

void	eval_percent(t_conv *conv)
{
	char		*str;

	str = ft_strdup("%");
	conv->alt_form = 0;
	str = apply_generic_precision(conv, &str, ft_strlen(str));
	str = apply_generic_width(conv, &str, ft_strlen(str), 0);
	conv->res = str;
}
