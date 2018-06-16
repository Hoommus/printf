/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:16:11 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/06/15 17:53:23 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include "libft/libft.h"

# define CONVERSIONS "diouxXDOUaAeEfFgGcCsSpn%"
# define MODIFIERS "lhjtzq"
# define SIGNED "diaAeEfFgG"
# define FLAGS "0\\L*#- +123456789."
# define NUMERIC "dDioOuUxXp"
# define NUMERIC_EXT "dDioOuUxXaAeEfFgG"
# define FLOATING "aAeEfFgG"
# define ITOA_UPPER "0123456789ABCDEF"
# define ITOA_LOWER "0123456789abcdef"
# define ABS(a) (a < 0 ? -(a) : a)

static size_t	g_pb_size = 128;
static int		g_symbols = 0;
int				g_error;

int				ft_printf(const char *restrict format, ...);

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

/*
** TODO: Make these memory-efficient by making bitwise flags in integer
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
	char		modif;
	long		next_arg;
	long		precision;
	long		min_width;
	char		conv;
	char		*formatted;
	char		*res;
	size_t		format_offset;
}				t_conv;

void			bufferize(char *s, long long len);
void			free_conv(t_conv **conv);
t_conv			*create_empty(void);
t_conv			*resolve(char *str, va_list arg);
void			find_eval_print(char *format, va_list list);

/*
** Parsing
*/
int				find_flags(char *str, t_conv *conv);
int				guess_convertion(char *str, t_conv *conv);
int				set_modifier_bits(char *str, t_conv *conv);

/*
** Number-related
*/
char			*utos_base(unsigned long long int nbr, int base, int var);
char			*itos_base(long long int nbr, int base);

/*
** Unicode
*/
char			*to_unicode(wchar_t codepoint);
char			*to_unicode_string(wchar_t *string);

/*
** Generic
*/
char			*apply_generic_width(t_conv *conv, char **str,
									 size_t len, char c);
char			*apply_generic_precision(t_conv *conv, char **str, size_t len);
char			*apply_unicode_precision(t_conv *conv, char **str);
char			*apply_alternate_form_ox(t_conv *conv, char **str);
char			*apply_sign(t_conv *conv, char **str, int sign);
char			*apply_space(t_conv *conv, char **str);
void			override_flags(t_conv *conv, long long int nbr);

/*
** Evals
*/
void			eval_di(t_conv *conv, va_list arg);
void			eval_uoxx(t_conv *conv, va_list arg);
void			eval_p(t_conv *conv, va_list arg);
void			eval_cs(t_conv *conv, va_list arg);
void			eval_percent(t_conv *conv);
void			eval_invalid(t_conv *conv);
char			*itoxx(t_conv *conv, unsigned long long nbr);
char			*itoo(t_conv *conv, unsigned long long nbr);
char			*itou(t_conv *conv, unsigned long long nbr);
char			*itod(t_conv *conv, long long int nbr);

#endif
