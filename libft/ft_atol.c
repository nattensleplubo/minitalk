/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:43:44 by ngobert           #+#    #+#             */
/*   Updated: 2022/01/18 14:12:06 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	el_atol;
	long	is_negative;
	int		i;

	el_atol = 0;
	is_negative = 1;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				is_negative = -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			el_atol = (el_atol * 10) + str[i] - 48;
			i++;
		}
		return (el_atol * is_negative);
	}
	return (0);
}
