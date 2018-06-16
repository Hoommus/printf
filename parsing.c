/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:41:29 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/06/06 18:47:20 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		guess_flag(char c, t_conv *conv)
{
	if (c == '0')
		conv->zero_padding = 'z';
	else if (ft_isdigit(c))
		return (0);
	else if (c == '#')
		conv->alt_form = '#';
	else if (c == '-')
		conv->pad_dir = '-';
	else if (c == ' ')
		conv->space = ' ';
	else if (c == '+')
		conv->sign = '+';
	else if (c == 'L')
		conv->long_afeg = 'L';
	else if (c == '\'')
		conv->apostrophe = '\'';
	else
		return (0);
	return (1);
}

int		find_flags(char *str, t_conv *conv)
{
	int		i;

	i = 0;
	while (ft_strchr(FLAGS, str[i]))
	{
		guess_flag(str[i], conv);
		if (ft_isdigit(str[i]) && str[i] != '0' && str[i - 1] != '.'
			&& conv->min_width == -1)
		{
			conv->min_width = ft_atoi(str + i);
			i += ft_nbrlen(conv->min_width) - 1;
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

int		guess_convertion(char *str, t_conv *conv)
{
	if (ft_strchr(CONVERSIONS, *str) != 0)
		conv->conv = *str;
	if (conv->conv == 'D' || conv->conv == 'O' || conv->conv == 'U'
		|| conv->conv == 'C' || conv->conv == 'S')
	{
		conv->modif = conv->modif | 12;
		conv->conv = (char)ft_tolower(conv->conv);
	}
	return (conv->conv == 0 ? 0 : 1);
}

int		set_modifier_bits(char *str, t_conv *conv)
{
	int		i;

	i = 0;
	while (ft_strchr(MODIFIERS, str[i]) != NULL)
	{
		if (ft_strnstr(str, "ll", 2))
		{
			conv->modif |= 8;
			i++;
		}
		else if (ft_strnstr(str, "hh", 2))
		{
			conv->modif |= 1;
			i++;
		}
		else if (*str == 'h')
			conv->modif |= 2;
		else if (*str == 'l')
			conv->modif |= 4;
		else if (*str == 'j')
			conv->modif |= 16;
		else if (*str == 't')
			conv->modif |= 32;
		else if (*str == 'z')
			conv->modif |= 64;
		else
			break ;
		i++;
	}
	return (i);
}
