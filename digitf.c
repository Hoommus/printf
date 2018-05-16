/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:43:24 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/16 17:22:07 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_precision(t_conv *conv, char *str, int len)
{
	int		i;
	char	pad;

	pad = ' ';
	if (conv->zero_padding != 0 && conv->conv != 'n')
		pad = '0';

}

char	*itoxx(t_conv *conv, unsigned long long nbr)
{
	char	*swap;
	char	*new;
	int		i;
	size_t	len;

	i = 0;
	new = utos_base(nbr, 16, conv->conv == 'x' ? 0 : 1);
	len = ft_strlen(new);
	len = len < conv->precision ? (size_t)conv->precision : len;
	if (conv->alt_form != 0 && nbr != 0)
	{
		swap = ft_strnew(2 + len);
		swap[0] = '0';
		swap[1] = conv->conv == 'x' ? 'x' : 'X';
		i = 2;
		while (i < conv->precision - len)
			swap[i++] = '0';
		ft_strcat(swap, new);
		free(new);
		new = swap;
	}
	return (new);
}

void	eval_di(t_conv *conv, va_list arg)
{
	long long int	d;

	if (ft_strnstr(conv->mod, "ll", 2) || conv->mod[0] == 'z')
		d = va_arg(arg, long long int);
	else if (ft_strnstr(conv->mod, "hh", 2))
		d = va_arg(arg, int);
	else if (conv->mod[0] == 'h')
		d = va_arg(arg, short);
	else if (conv->mod[0] == 'l')
		d = va_arg(arg, long);
	else if (conv->mod[0] == 't')
		d = va_arg(arg, ptrdiff_t);
//	else if (conv->mod[0] == 'j')
//		d = va_arg(arg, intmax_t);
	else
		d = va_arg(arg, intmax_t);
	conv->res = itos_base(d, 10);
}

void	eval_uoxx(t_conv *conv, va_list arg)
{
	unsigned long long int	d;

	if (ft_strnstr(conv->mod, "ll", 2))
		d = va_arg(arg, unsigned long long int);
	else if (ft_strnstr(conv->mod, "hh", 2))
		d = va_arg(arg, unsigned int);
	else if (conv->mod[0] == 'h')
		d = va_arg(arg, unsigned short);
	else if (conv->mod[0] == 'l')
		d = va_arg(arg, unsigned long);
	else if (conv->mod[0] == 't')
		d = (unsigned long long int)va_arg(arg, ptrdiff_t);
	else if (conv->mod[0] == 'z')
		d = va_arg(arg, size_t);
//	else if (conv->mod[0] == 'j')
//		d = va_arg(arg, uintmax_t);
	else
		d = va_arg(arg, uintmax_t);
	if (conv->conv == 'o')
		conv->res = utos_base(d, 8, 0);
	else if (conv->conv == 'x' || conv->conv == 'X')
		conv->res = itoxx(conv, d);
}
