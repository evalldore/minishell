/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:33:12 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/17 20:39:34 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_debug_child(int pid, int status)
{
	int		exit;

	if (WIFEXITED(status))
	{
		exit = WEXITSTATUS(status);
		printf("Child process (PID %d) exited with status: %d\n", pid, exit);
	}
	else
		printf("Child process (PID %d) did not exit normally.\n", pid);
}
