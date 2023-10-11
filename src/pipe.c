/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:21:18 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/10 20:38:45 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	close_pipe(int fd_pipe[2], int pid[2])
{
	close_fds(fd_pipe);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

void	ms_pipe(t_cmd *left, t_cmd *right)
{
	int		p_id[2];
	int		fd_pipe[2];

	if (pipe(fd_pipe) < 0)
		ms_terminate(1, "Minishell: pipe failed to init!\n");
	p_id[0] = fork();
	if (p_id[0] < 0)
		ms_terminate(1, "Minishell: fork failed to init!\n");
	if (p_id[0] == 0)
	{
		dup2(fd_pipe[0], STDIN_FILENO);
		close_fds(fd_pipe);
		ms_cmd_run(right);
	}
	p_id[1] = fork();
	if (p_id[1] < 0)
		ms_terminate(1, "Minishell: fork failed to init!\n");
	if (p_id[1] == 0)
	{
		dup2(fd_pipe[1], STDOUT_FILENO);
		close_fds(fd_pipe);
		ms_cmd_run(left);
	}
	close_pipe(fd_pipe, p_id);
}
