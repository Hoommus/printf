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
	new->flags = ft_strnew(FLAGS_SIZE + 1);
	new->conv = NULL;
	new->res = NULL;
	new->format_offset = 0;
	return (new);
}

void	free_conv(t_conv **conv)
{
	if (conv == NULL || *conv == NULL)
		return ;
	free((*conv)->conv);
	free((*conv)->res);
	free(*conv);
	*conv = NULL;
}

int		add_flag(char flag, t_conv *conv)
{
	int i;

	i = 0;
	while (conv->flags[i++])
		;
	while (!has_flag(flag, conv))
	{

	}
}
