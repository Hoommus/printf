/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:46:38 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/05/03 15:49:38 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_utf_strlen(unsigned char *str)
{
	unsigned long	i;
	int				mask;

	mask = 128;
	i = 0;
	while (str[i])
	{

		i++;
	}
	return (i);
}
