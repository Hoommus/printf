/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:49:03 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/05 14:49:03 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen(long long nbr)
{
	int		i;

	if (nbr == 0)
		return (1);
	i = 0;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}
