/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:59:36 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/15 16:51:05 by vtarasiu         ###   ########.fr       */
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
	new->res_length = -1;
	new->min_width = -1;
	new->precision = -1;
	new->long_afeg = 0;
	new->next_arg = 0;
	new->pad_dir = '+';
	new->modif = 0;
	new->conv = 0;
	new->res = NULL;
	new->mod = 0;
	return (new);
}

void	free_conv(t_conv **conv)
{
	if (conv == NULL || *conv == NULL)
		return ;
	free((*conv)->res);
	free(*conv);
	*conv = NULL;
}
