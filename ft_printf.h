/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:16:11 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/03 18:10:01 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft/libft.h"

size_t	g_pb_size = 128;

int		ft_printf(const char *restrict format, ...);

typedef struct	s_conv
{
	char		*conv;
	char		*res;
//	size_t		conv_size;
}				t_conv;

#endif
