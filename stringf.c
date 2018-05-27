/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:35:00 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/25 18:49:32 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	eval_cs(t_conv *conv, va_list arg)
{
	char	*str;

	if (conv->conv == 's' || conv->conv == 'S')
		if (conv->mod[0] == 'l' || conv->conv == 'S')
			str = to_unicode_string(va_arg(arg, wchar_t *));
		else
			str = ft_strdup(va_arg(arg, char *));
	else if (conv->conv == 'c' || conv->conv == 'C')
		if (conv->mod[0] == 'l' || conv->conv == 'C')
			str = to_unicode((wchar_t)va_arg(arg, long));
		else
			str = to_unicode((wchar_t)va_arg(arg, int));
	str = apply_generic_precision(conv, &str, ft_strlen(str));
	str = apply_generic_width(conv, &str, ft_strlen(str));
	conv->res = str;
}

/*
void	eval_s(t_conv *conv, va_list arg)
{
	char	*str;

	if (conv->mod[0] == 'l' || conv->conv == 'S')
		str = to_unicode_string(va_arg(arg, wchar_t *));
	else
		str = to_unicode_string((wchar_t *)va_arg(arg, char *));
	str = apply_generic_precision(conv, &str, ft_strlen(str));
	str = apply_generic_width(conv, &str, ft_strlen(str));
	conv->res = str;
}

void	eval_c(t_conv *conv, va_list arg)
{
	char	*str;
	long	l;

	if (conv->mod[0] == 'l' || conv->conv == 'C')
	{
		l = va_arg(arg, long);
		str = to_unicode((wchar_t)l);
	}
	else
	{
		l = va_arg(arg, int);
		str = to_unicode((unsigned char)l);
	}
	str = apply_generic_precision(conv, &str, ft_strlen(str));
	str = apply_generic_width(conv, &str, ft_strlen(str));
	conv->res = str;
}
*/