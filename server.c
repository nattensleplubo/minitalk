/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:29:47 by ngobert           #+#    #+#             */
/*   Updated: 2022/01/19 19:08:47 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_minitalk	g_char;

void	global_init(void)
{
	g_char.c = 0;
	g_char.bits = 7;
}

void	kill_to_client(int sig)
{
	if (kill(g_char.pid, SIGUSR1) == -1)
		ft_printf("Error: kill failed\n");
}

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
			kill_to_client(SIGUSR1);
		}
		else
			g_char.str = ft_charjoin(g_char.str, g_char.c);
		global_init();
	}
	kill_to_client(SIGUSR1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	struct sigaction	sig;
	pid_t				pid;
	
	if (argc != 1)
		return (ft_printf("Too much arguments...\n"), -1);
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sig_handler;
	global_init();
	g_char.str = NULL;
	print_menu();
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
}
