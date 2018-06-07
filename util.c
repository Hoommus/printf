/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:59:36 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/06/06 16:21:43 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv	*create_empty(void)
{
	t_conv	*new;

	new = (t_conv *)malloc(sizeof(t_conv));
	if (new == NULL)
		return (NULL);
	new->format_offset = 0;
	new->zero_padding = 0;
	new->min_width = -1;
	new->precision = -1;
	new->long_afeg = 0;
	new->next_arg = 0;
	new->pad_dir = '+';
	new->modif = 0;
	new->conv = 0;
	new->sign = 0;
	new->res = NULL;
	return (new);
}

void	free_conv(t_conv **conv)
{
	if (conv == NULL || *conv == NULL)
		return ;
	ft_bzero(*conv, sizeof(conv));
	free((*conv)->res);
	free(*conv);
	*conv = NULL;
}

void	find_eval_print(char *format, va_list list)
{
	char		*percent;
	t_conv		*conv;

	while (*format)
	{
		percent = ft_strchr(format, '%');
		if (percent > format)
		{
			bufferize(format, percent - format);
			format += percent - format;
		}
		else if (percent == NULL)
		{
			bufferize(format, ft_strlen(format));
			break ;
		}
		bufferize((conv = resolve(percent, list))->res, -1);
		format += conv->format_offset != 0 ? conv->format_offset : 1;
		free_conv(&conv);
	}
}
