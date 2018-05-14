/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:16:11 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/05 14:48:59 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft/libft.h"

# define CONVERSIONS "diouxXDOUaAeEfFgGcCsSpn%"

static size_t	g_pb_size = 128;

int		ft_printf(const char *restrict format, ...);

/*
** Following chars respectively:
** '#' - alternate form
** '0' - For all conversions except n, the converted value is padded on the left
**       with zeros rather than blanks
** '-' - value is to be left adjusted on the field
** ' ' - blank before positive number of signed conversion
** '+' - always put sign before conversion
** ''' - grouped and separated by thousands
** long_afeg = 'L' modifier for aAeEfFgG
** modifier  = generic modifier
*/

typedef struct	s_conv
{
	char		zero_padding;
	char		alt_form;
	char		pad_dir;
	char		space;
	char		sign;
	char		apostrophe;
	char		separator;
	char		long_afeg;
	char		modifier[2];
	long		next_arg;
	long		precision;
	long		min_width;
	char		conv;
	char		*res;
	size_t		format_offset;
}				t_conv;

void	free_conv(t_conv **conv);
t_conv	*create_empty(void);
t_conv	*resolve(char *str);

#endif
