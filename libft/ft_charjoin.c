/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:53:54 by ngobert           #+#    #+#             */
/*   Updated: 2022/01/19 17:58:25 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*char_to_str(char c)
{
	char	*str;
	
	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_charjoin(char *str, char c)
{
	char	*new;
	int		i;
	
	i = 0;
	if (!c)
		return (NULL);
	if (!str)
		return (char_to_str(c));
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (free(str), NULL);
	while (str[i])
		i += (new[i] = str[i], 1);
	free(str);
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}