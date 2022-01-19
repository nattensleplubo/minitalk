/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:29:47 by ngobert           #+#    #+#             */
/*   Updated: 2022/01/19 23:49:58 by ngobert          ###   ########.fr       */
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
	if (kill(g_char.pid, sig) == -1)
		ft_printf("Error: kill failed\n");
}

static char	*print_string(char *str)
{
	ft_printf("\nPID [");
	ft_printf("%d", g_char.pid);
	ft_printf("] >> ");
	if (!str)
		ft_printf("\n");
	else
		ft_printf("%s\n", str);
	free(g_char.str);
	return (NULL);
}

void	bits_to_char(int signum, siginfo_t *siginfo, void *context)
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
			g_char.str = print_string(g_char.str);
			kill_to_client(SIGUSR2);
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
	
	if (argc != 1)
		return (ft_printf("Too much arguments...\n"), -1);
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = bits_to_char;
	global_init();
	g_char.str = NULL;
	print_menu();
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
}
