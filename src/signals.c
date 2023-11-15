/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:33:49 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/15 14:39:17 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_input(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	interrupt(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	ms_terminate(130, NULL);
}

void	ms_signal_set(int mode)
{
	if (mode == MODE_DEFAULT)
	{
		signal(SIGINT, clear_input);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == MODE_IGN)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == MODE_MAIN)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == MODE_HEREDOC)
	{
		signal(SIGINT, interrupt);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		ft_putstr_fd("Minishell: Signal mode invalid\n", 2);
}
