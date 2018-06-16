/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:36:50 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/06/07 15:34:52 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	override_flags(t_conv *conv, long long int nbr)
{
	if (conv->pad_dir == '-')
		conv->zero_padding = 0;
	if (ft_strchr(NUMERIC, conv->conv) != NULL && conv->precision != -1)
		conv->zero_padding = 0;
	if (ft_strchr(SIGNED, conv->conv) != NULL && conv->sign != 0)
		conv->space = 0;
	if (nbr < 0)
		conv->sign = '+';
}

size_t	nbr_len(long long int nbr, int base)
{
	size_t					i;
	unsigned long long int	u_nbr;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr == LLONG_MIN)
		u_nbr = (unsigned long long int)-(nbr + 1) + 1;
	else
		u_nbr = (unsigned long long int)(nbr);
	while (u_nbr)
	{
		u_nbr /= base;
		i++;
	}
	return (i);
}

/*
** var (variant) is used to determine if letters should have upper or lower case
** 0 == lower
** 1 == upper
*/

char	*utos_base(unsigned long long int nbr, int base, int var)
{
	size_t	len;
	char	*str;

	if (nbr != ULONG_MAX)
		len = nbr_len(nbr, base);
	else if (base == 8)
		len = 22;
	else if (base == 10)
		len = 20;
	else
		len = 16;
	str = ft_strnew(len);
	if (nbr == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nbr)
	{
		str[len--] = var == 1 ? ITOA_UPPER[nbr % base] : ITOA_LOWER[nbr % base];
		nbr /= base;
	}
	return (str);
}

char	*itos_base(long long int nbr, int base)
{
	size_t	len;
	char	*str;

	len = nbr < 0 && base == 10 ? 1 : 0;
	len += nbr_len(nbr, base);
	str = ft_strnew(len);
	if (base == 10 && nbr < 0)
		str[0] = '-';
	if (nbr == 0)
		str[0] = '0';
	str[len] = '\0';
	while (nbr)
	{
		str[--len] = ITOA_LOWER[ABS(nbr % base)];
		nbr /= base;
	}
	return (str);
}
