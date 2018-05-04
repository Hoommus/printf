/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 17:15:46 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/04 17:16:24 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		has_flag(char c, struct s_conv *self)
{
	if (ft_strchr(self->flags, c))
		return (1);
	else
		return (0);
}