/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:15:28 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/05 15:04:22 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Returns (i - 1) because
*/
int		find_flags(char *str, t_conv *conv)
{
	int		i;

	i = 0;
	while ((!ft_isalpha(str[i]) || str[i] == 'L'))
	{
		conv->zero_padding = str[i] == '0' ? 'z' : conv->zero_padding;
		conv->apostrophe = str[i] == '\'' ? '\'' : conv->apostrophe;
		conv->long_afeg = str[i] == 'L' ? 'L' : conv->long_afeg;
		conv->alt_form = str[i] == '#' ? '#' : conv->alt_form;
		conv->pad_dir = str[i] == '-' ? '-' : conv->pad_dir;
		conv->space = str[i] == ' ' ? ' ' : conv->space;
		conv->sign = str[i] == '+' ? '+' : conv->sign;
		if (ft_isdigit(str[i]) && str[i] != '0' && str[i - 1] != '.')
        {
            conv->min_width = ft_atoi(str + i);
			i += ft_nbrlen(conv->min_width);
        }
		if (str[i] == '.' && conv->precision == -1)
		{
			conv->precision = ft_atoi(str + i + 1);
			i += ft_nbrlen(conv->precision);
		}
		i++;
	}
	return (i - 1);
}

int		guess_convertion(char *str, t_conv *conv)
{
	if (ft_strchr(CONVERSIONS, *str) != 0)
	{
		conv->conv = *str;
		return (1);
	}
	return (0);
}

char	*set_modifier(char *str, t_conv *conv)
{
	if (ft_strnstr(str, "ll", 2))
	{
		conv->modifier[0] = 'l';
		conv->modifier[1] = 'l';
	}
	else if (ft_strnstr(str, "hh", 2))
	{
		conv->modifier[0] = 'h';
		conv->modifier[1] = 'h';
	}
	else if (ft_strnstr(str, "h", 1))
		conv->modifier[0] = 'h';
	else if (ft_strnstr(str, "l", 1))
		conv->modifier[0] = 'l';
	else if (ft_strnstr(str, "j", 1))
		conv->modifier[0] = 'j';
	else if (ft_strnstr(str, "t", 1))
		conv->modifier[0] = 't';
	else if (ft_strnstr(str, "z", 1))
		conv->modifier[0] = 'z';
	else
		return (NULL);
	return (conv->modifier);
}

//t_conv	*resolve(char *str, va_list arg)
t_conv	*resolve(char *str)
{
	t_conv			*new;
	char			*copy;

	copy = str;
	new = create_empty();
	str += find_flags(str, new);
	str += ft_strlen(set_modifier(str, new));
	str += guess_convertion(str, new);
	new->format_offset = str < copy ? copy - str : str - copy;

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
		bufferize((conv = resolve(percent/*, list*/))->res, -1);
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
