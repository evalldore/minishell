/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:33:12 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/07 00:04:14 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_debug_child(int pid, int status)
{
	int		exit;
	int		sig;

	if (!DEBUG)
		return;
	if (WIFEXITED(status))
	{
		exit = WEXITSTATUS(status);
		printf("Child process (PID %d) exited with status: %d\n", pid, exit);
	}
	else
	{
		printf("Child process (PID %d) did not exit normally.\n", pid);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			printf("Child process (PID %d) terminated by signal %d\n", pid, sig);
		}
	}
}
