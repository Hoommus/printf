/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:16:11 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/04 18:47:21 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft/libft.h"

# define FLAGS_SIZE 8

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
**
*/

typedef struct	s_conv
{
	char		alt_form;
	char		zero_padding;
	char		pad_dir;
	char		space;
	char		sign;
	char		groups;
	char		separator;
	char		long_afeg;
	char		*modifier;
	int			next_arg;
	int			precision;
	int			min_width;
	char		*flags;
	char		*conv;
	char		*res;
	size_t		format_offset;
	int			(*has_flag)(char c, struct s_conv *self);
}				t_conv;

int		has_flag(char c, struct s_conv *conv);
void	free_conv(t_conv **conv);
t_conv	*create_empty(void);

#endif
