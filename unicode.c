/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:17:56 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/23 18:18:23 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*to_unicode(wchar_t codepoint)
{
	char	*bytes;

	bytes = ft_strnew(4);
	if (codepoint <= 0x7F)
		bytes[0] = (char)codepoint;
	else if (codepoint <= 0x7FF)
	{
		bytes[0] = (char)(0xC0 | ((codepoint >> 6) & 0x1F));
		bytes[1] = (char)(0x80 | (codepoint & 0x3F));
	}
	else if (codepoint <= 0xFFFF)
	{
		bytes[0] = (char)(0xE0 | ((codepoint >> 12) & 0x0F));
		bytes[1] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
		bytes[2] = (char)(0x80 | (codepoint & 0x3F));
	}
	else if (codepoint <= 0x10FFFF)
	{
		bytes[0] = (char)(0xF0 | ((codepoint >> 18) & 0x07));
		bytes[1] = (char)(0x80 | ((codepoint >> 12) & 0x3F));
		bytes[2] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
		bytes[3] = (char)(0x80 | (codepoint & 0x3F));
	}
	return (bytes);
}

char	*to_unicode_string(wchar_t *s)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strnew(ft_wchar_strlen(s));
	while (s[i])
	{
		ft_strcat(str, to_unicode(s[i]));
		i++;
	}
	return (str);
}