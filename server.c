/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:29:47 by ngobert           #+#    #+#             */
/*   Updated: 2022/01/19 16:52:14 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_minitalk	g_char;

void	sig_handler(int signum, siginfo_t *siginfo, void *context)
{
	int	bit;
	
	(void)context;
	if ((siginfo)->si_pid)
		g_char.pid = siginfo->si_pid;
	if (signum == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	g_char.c += bit << g_char.bits;
	g_char.bits--;
	if (g_char.bits == -1)
	{
		if (!g_char.c)
		{
			g_char.str = (ft_printf("%s\n", g_char.str), NULL);
		}
		else
			g_char.str
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	struct sigaction	sig;
	pid_t				pid;
	
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sig_handler;
}
