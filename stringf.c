/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:35:00 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/23 18:25:35 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_printf.h"

void	eval_s(t_conv *conv, va_list arg)
{
	char		*str;

	if (conv->mod[0] == 'l')
	{
		str = to_unicode_string(va_arg(arg, wchar_t *));

	}
	else
	{
		str = to_unicode_string((wchar_t *)va_arg(arg, char *));

	}
}

void	eval_c(t_conv *conv, va_list arg)
{
	wchar_t		c;
	long		l;

	if (conv->mod[0] == 'l')
	{
		l = va_arg(arg, long);
		conv->res = to_unicode((wchar_t)l);
	}
	else
	{
		l = va_arg(arg, int);
		conv->res = to_unicode((unsigned char)l);
	}
}