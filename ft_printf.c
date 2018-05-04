/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:15:28 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/04 18:46:07 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv	*find_flags(char *str, t_conv *conv)
{
	int		i;

	i = 0;
	while (str[i])
	{
		conv->alt_form = str[i] == '#' ? '#' : conv->alt_form;
		conv->pad_dir = str[i] == '-' ? '-' : conv->pad_dir;
		conv->zero_padding = str[i] == '0' ? '0' : conv->zero_padding;
		conv->space = str[i] == ' ' ? ' ' : conv->space;
		conv->sign = str[i] == '+' ? '+' : conv->sign;
		conv->groups = str[i] == '\'' ? '\'' : conv->groups;
		conv->long_afeg = str[i] == 'L' ? 'L' : conv->long_afeg;
		conv->groups = str[i] == '\'' ? '\'' : conv->groups;
		conv->groups = str[i] == '\'' ? '\'' : conv->groups;
		if (str[i] == '.')
			conv->precision = ft_atoi(str + i + 1);
		if (ft_isdigit(str[i]) && str[i - 1] != '.')
			conv->min_width = ft_atoi(str + i);
		i++;
	}
}

t_conv	*resolve(char *str, va_list arg)
{
	t_conv	*new;

	new = create_empty();
	find_flags(str, new);
	return NULL;
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
