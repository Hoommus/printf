/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integerf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:43:24 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/06/06 20:26:50 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*trimxx(t_conv *conv, char **str)
{
	size_t	i;
	char	*swap;

	swap = *str;
	i = ft_strlen(*str);
	if (i > 8 && conv->modif < 4 && i - 8 > 0)
	{
		swap = ft_strsub(*str, i - 8, i);
		ft_strdel(str);
	}
	if (ft_strequ(swap, "00000000"))
	{
		ft_strdel(&swap);
		swap = ft_strdup("0");
	}
	return (swap);
}

char	*itoxx(t_conv *conv, unsigned long long nbr)
{
	char	*new;

	if ((nbr == 0 && conv->precision == 0) ||
			(conv->conv == 'p' && conv->precision == 0))
		new = ft_strnew(0);
	else
		new = utos_base(nbr, 16, conv->conv == 'X' ? 1 : 0);
	if (conv->modif < 8 && conv->modif != 0)
		new = trimxx(conv, &new);
	new = apply_generic_precision(conv, &new, ft_strlen(new));
	if (conv->alt_form != 0 && conv->min_width > -1 && conv->zero_padding != 0)
	{
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
		if ((conv->alt_form != 0 && nbr != 0) || conv->conv == 'p')
			new = apply_alt_form_oxx(conv, &new);
	}
	else
	{
		if (nbr != 0 || conv->conv == 'p')
			new = apply_alt_form_oxx(conv, &new);
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
	}
	return (new);
}

char	*itoo(t_conv *conv, unsigned long long nbr)
{
	char	*new;

	if (nbr == 0 && conv->precision == 0 && conv->alt_form == 0)
		new = ft_strnew(0);
	else
		new = utos_base(nbr, 8, 0);
	new = apply_generic_precision(conv, &new, ft_strlen(new));
	if (nbr != 0)
		new = apply_alt_form_oxx(conv, &new);
	if (conv->precision != -1)
		new = apply_generic_width(conv, &new, ft_strlen(new), ' ');
	else
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
	return (new);
}

char	*itou(t_conv *conv, unsigned long long nbr)
{
	char	*new;

	new = utos_base(nbr, 10, 0);
	new = apply_generic_precision(conv, &new, ft_strlen(new));
	if (nbr != 0)
		new = apply_alt_form_oxx(conv, &new);
	if (conv->precision != -1)
		new = apply_generic_width(conv, &new, ft_strlen(new), ' ');
	else
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
	return (new);
}

void	override_flags(t_conv *conv, long long int nbr)
{
	if (conv->pad_dir == '-')
		conv->zero_padding = 0;
	if (ft_strchr(NUMERIC, conv->conv) != NULL && conv->precision != -1)
		conv->zero_padding = 0;
	if (conv->sign != 0)
		conv->space = 0;
	if (nbr < 0)
		conv->sign = '+';
}

char	*itod(t_conv *conv, long long int nbr)
{
	char	*new;

	new = nbr == LLONG_MIN ? ft_strdup("9223372036854775808") : itos_base(ABS(nbr), 10);
	override_flags(conv, nbr);
	new = apply_generic_precision(conv, &new, ft_strlen(new));
	if (conv->zero_padding == 0)
	{
		new = apply_sign_or_space(conv, &new, nbr < 0 ? -1 : 1);
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
	}
	else
	{
		new = apply_generic_width(conv, &new, ft_strlen(new), 0);
		new = apply_sign_or_space(conv, &new, nbr < 0 ? -1 : 1);
	}
	return (new);
}
