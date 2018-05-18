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
}

t_conv	*resolve(char *str, va_list arg)
{
	t_conv			*new;
	char			*copy;

	copy = str;
	new = create_empty();
	str += find_flags(str, new);
	str += ft_strlen(set_modifier(str, new));
	str += guess_convertion(str, new);
	new->format_offset = str < copy ? copy - str : str - copy;
	eval(new, arg);
	return (new);
}

void	bufferize(char *s, long long len)
{
	static unsigned char	*buffer = NULL;
	static unsigned long	i;

	buffer = buffer == NULL ? (unsigned char *)ft_strnew(g_pb_size) : buffer;
	if (s == NULL && len == -1)
		free(buffer);
	len = len < 0 ? ft_strlen(s) : len;
	while (i < g_pb_size && len--)
		buffer[i++] = (unsigned char)*s++;
	if (i == g_pb_size)
	{
		write(1, buffer, g_pb_size);
		i = 0;
	}
	if (len != 0)
		bufferize(s, len);
}

/*
** Function resolves $ and * modifiers
*/
void	preprocess(char *format, va_list args)
{
/*
** STUB
*/
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		list;
	t_conv		*conv;
	char		*copy;
	char		*percent;

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
		bufferize((conv = resolve(percent, list))->res, -1);
		copy += conv->format_offset;
		free_conv(&conv);
		copy++;
	}
	bufferize(NULL, -1);
	va_end(list);
	/*
	va_start(ap, fmt);
	va_copy(ap2, ap);
	while (*fmt)
		switch(*fmt++) {
			case 's':
				s = va_arg(ap, char *);
			case 'd':
				d = va_arg(ap, int);
			case 'c':
				 Note: char is promoted to int.
				c = va_arg(ap, int);
		}
	va_end(ap);
	va_end(ap2);
	*/
	return (0);
}
