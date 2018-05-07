/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:59:36 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/04 17:40:20 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv	*create_empty(void)
{
	t_conv	*new;

	new = (t_conv *)malloc(sizeof(t_conv));
	if (new == NULL)
		return (NULL);
	new->modifier[1] = '8';
	new->min_width = -1;
	new->precision = -1;
	new->next_arg = '8';
	new->long_afeg = '8';
	new->pad_dir = '8';
	new->conv = '8';
	new->res = NULL;
	new->format_offset = 0;
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
