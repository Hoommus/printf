/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:15:28 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/18 17:27:29 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	eval(t_conv *conv, va_list arg)
{
	if (conv->conv == 'd' || conv->conv == 'i')
		eval_di(conv, arg);
	else if (conv->conv == 'o' || conv->conv == 'x' || conv->conv == 'X'
			|| conv->conv == 'u')
		eval_uoxx(conv, arg);
	else if (conv->conv == 'c' || conv->conv == 's')
		eval_cs(conv, arg);
	else if (conv->conv == 'p')
		eval_p(conv, arg);
}

/*
** TODO: Add empty conversion handling
*/

t_conv	*resolve(char *str, va_list arg)
{
	t_conv			*conv;
	char			*copy;

	copy = str;
	conv = create_empty();
	str++;
	str += find_flags(str, conv);
	str += set_modifier(str, conv);
	str += guess_convertion(str, conv);
	if (conv->conv == 'D' || conv->conv == 'O' || conv->conv == 'U')
	{
		conv->mod = 'l';
		conv->conv = (char)ft_tolower(conv->conv);
	}
	conv->format_offset = str < copy ? copy - str : str - copy;
	eval(conv, arg);
	return (conv);
}

void	bufferize(char *s, long long len)
{
	static unsigned char	*buffer = NULL;
	static unsigned long	i;

	buffer = buffer == NULL ? (unsigned char *)ft_strnew(g_pb_size) : buffer;
	len = len < 0 ? ft_strlen(s) : len;
	while (i < g_pb_size && len--)
	{
		buffer[i++] = (unsigned char)*s++;
		g_symbols++;
	}
	if (s == NULL && len == -1)
	{
		write(1, buffer, i);
		ft_strdel((char **)&buffer);
		i = 0;
	}
	else if (i == g_pb_size)
	{
		write(1, buffer, i);
		ft_bzero(buffer, g_pb_size);
		i = 0;
	}
	if (len > 0)
		bufferize(s, len);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		list;
	t_conv		*conv;
	char		*copy;
	char		*percent;

	g_symbols = 0;
	while (ft_strlen((char *)format) > g_pb_size * 1.2)
		g_pb_size <<= 1;
	va_start(list, format);
	copy = (char *)format;
	while (*copy)
	{
		percent = ft_strchr(copy, '%');
		if (percent > copy)
		{
			bufferize(copy, percent - copy);
			copy += percent - copy;
		}
		else if (percent == NULL)
		{
			bufferize(copy, ft_strlen(copy));
			break ;
		}
		bufferize((conv = resolve(percent, list))->res, -1);
		copy += conv->format_offset != 0 ? conv->format_offset : 1;
		free_conv(&conv);
	}
	bufferize(NULL, -1);
	va_end(list);
	return (g_symbols);
}
