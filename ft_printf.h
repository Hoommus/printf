/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:16:11 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/15 11:29:03 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stddef.h>

# include <stdarg.h>
# include <stdlib.h>
# include "libft/libft.h"

# define CONVERSIONS "diouxXDOUaAeEfFgGcCsSpn%"
# define ITOA_DIGITS "0123456789ABCDEF"
# define ABS(a) (a < 0 ? -(a) : a)

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
** long_afeg = 'L' mod for aAeEfFgG
** mod  = generic mod
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
	char		mod[2];
	long		next_arg;
	long		precision;
	long		min_width;
	char		conv;
	char		*formatted;
	char		*res;
	size_t		format_offset;
}				t_conv;

void	free_conv(t_conv **conv);
t_conv	*create_empty(void);
t_conv	*resolve(char *str, va_list arg);

/*
** Evals
*/
void	eval_di(t_conv *conv, va_list arg);

#endif
