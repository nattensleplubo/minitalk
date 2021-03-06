/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:29:14 by ngobert           #+#    #+#             */
/*   Updated: 2022/01/19 23:20:39 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_minitalk
{
	char	c;
	int		bits;
	char	*str;
	int		pid;
}	t_minitalk;

void	print_menu(void);
void	bits_to_char(int signum, siginfo_t *siginfo, void *context);

#endif