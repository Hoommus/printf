/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:41:29 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/22 17:09:34 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_flags(char *str, t_conv *conv)
{
	int		i;

	i = 0;
	while (ft_strchr(FLAGS, str[i]))
	{
		conv->zero_padding = str[i] == '0' ? 'z' : conv->zero_padding;
		conv->apostrophe = str[i] == '\'' ? '\'' : conv->apostrophe;
		conv->long_afeg = str[i] == 'L' ? 'L' : conv->long_afeg;
		conv->next_arg = str[i] == '*' ? 1 : conv->next_arg;
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
			if (ft_isdigit(str[i + 1]))
				i += ft_nbrlen(conv->precision);
		}
		i++;
	}
	return (i);
}

/*
** TODO: POSSIBLE BUG ALERT
*/

int		guess_convertion(char *str, t_conv *conv)
{
	if (ft_strchr(CONVERSIONS, *str) != 0)
		conv->conv = *str;
	if (conv->conv == 'C' || conv->conv == 'S')
		conv->modif = conv->modif | 8;
	return (conv->conv == 0 ? 0 : 1);
}

int		set_modifier_bits(char *str, t_conv *conv)
{
	int		i;

	i = 0;
	while (ft_strchr(MODIFIERS, str[i]) != NULL)
	{
		if (ft_strnstr(str, "ll", 2))
			conv->modif |= 8;
		else if (ft_strnstr(str, "hh", 2))
			conv->modif |= 1;
		else if (ft_strnstr(str, "h", 1))
			conv->modif |= 2;
		else if (ft_strnstr(str, "l", 1))
			conv->modif |= 4;
		else if (ft_strnstr(str, "j", 1))
			conv->modif |= 16;
		else if (ft_strnstr(str, "t", 1))
			conv->modif |= 32;
		else if (ft_strnstr(str, "z", 1))
			conv->modif |= 64;
		else
			continue ;
		i++;
	}
	return (i);
}

int		set_modifier(char *str, t_conv *conv)
{
	if (ft_strnstr(str, "ll", 2))
		conv->mod = 'L';
	else if (ft_strnstr(str, "hh", 2))
		conv->mod = 'H';
	else if (ft_strnstr(str, "h", 1))
		conv->mod = 'h';
	else if (ft_strnstr(str, "l", 1))
		conv->mod = 'l';
	else if (ft_strnstr(str, "j", 1))
		conv->mod = 'j';
	else if (ft_strnstr(str, "t", 1))
		conv->mod = 't';
	else if (ft_strnstr(str, "z", 1))
		conv->mod = 'z';
	else
		return (0);
	return (conv->mod == 'L' || conv->mod == 'H' ? 2 : 1);
}
