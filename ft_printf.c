/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:15:28 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/03 18:16:45 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv	*resolve(char *str, va_list arg)
{

}

void	bufferize(char *s, long long len)
{
	static unsigned char	buffer[g_pb_size];
	static unsigned long	i;
	unsigned long			j;

	j = 0;
	len = len < 0 ? ft_strlen(s) : len;
	while (i < g_pb_size)
	{
		buffer[i++] = (unsigned char)*s++;
		len--;
	}
	if (i == g_pb_size)
	{
		write(1, buffer, g_pb_size);
		i = 0;
	}
	if (len != 0)
		bufferize(s, len);
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
		//*******************//
		free(conv);
		//*******************//
		copy++;
	}
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
}
