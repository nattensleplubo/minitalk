/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:29:22 by ngobert           #+#    #+#             */
/*   Updated: 2022/01/20 11:55:43 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_minitalk g_minitalk;

static void	kill_to_server(int signum, int pid)
{
	if (kill(pid, signum) == -1)
	{
		ft_printf("Error: kill failed\n");
		exit (1);
	}
}

int		kill_null(int pid)
{
	size_t	i;
	
	i = 0;
	while (i <= 7)
	{
		kill_to_server(SIGUSR1, pid);
		usleep(500);
		i++;
	}
	return (1);
}

static void	char_to_bin(int pid, char *str)
{
	size_t	i;
	int		shift;
	
	i = 0;
	while (str[i])
	{
		shift = 7;
		while (shift >= 0)
		{
			if ((str[i] & (1 << shift)))
				kill_to_server(SIGUSR2, pid);
			else
				kill_to_server(SIGUSR1, pid);
			usleep(1000);
			shift--;
		}
		i++;
	}
	kill_null(pid);
}

void	sig_handler(int signum)
{
	static int	boolean = 1;
	
	if (signum == SIGUSR1 && boolean)
	{
		ft_printf("Server [%d], receiving...\n", g_minitalk.pid);
		boolean = 0;
	}
	if (signum == SIGUSR2)
	{
		ft_printf("Server [%d], received!\n", g_minitalk.pid);
		boolean = 1;
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3 && ft_str_all_digit(argv[1]))
	{
		signal(SIGUSR1, sig_handler);
		signal(SIGUSR2, sig_handler);
		g_minitalk.pid = ft_atoi(argv[1]);
		char_to_bin(ft_atoi(argv[1]), argv[2]);
		while (1)
			pause();
	}
}