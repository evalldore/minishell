/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:33:49 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/13 18:49:37 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	ms_terminate(130, NULL);
}

void	clear_input_redis(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	clear_input(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
}

static void	set_signal(int sig, int flags, void (*func)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_flags, sig);
	sa.sa_flags = flags;
	sa.sa_handler = func;
	sigaction(sig, &sa, NULL);
}

void	ms_signal_set(int mode)
{
	if (mode == MODE_DEFAULT)
	{
		set_signal(SIGINT, 0, clear_input_redis);
		set_signal(SIGQUIT, 0, SIG_IGN);
	}
	else if (mode == MODE_MAIN)
	{
		set_signal(SIGINT, 0, clear_input);
		set_signal(SIGQUIT, 0, SIG_IGN);
	}
	else if (mode == MODE_HEREDOC)
	{
		set_signal(SIGINT, SA_RESTART, terminate);
		set_signal(SIGQUIT, 0, SIG_IGN);
	}
	else
		ft_putstr_fd("Minishell: Signal mode invalid\n", 2);
}
