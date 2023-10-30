/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:21:18 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/26 19:28:51 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static int fork_cmd(t_cmd *cmd, int fd_pipe[2], int std)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		ms_terminate(1, "Minishell: Pipe fork failed to init!\n");
	if (pid == 0)
	{
		dup2(fd_pipe[std], std);
		close_fds(fd_pipe);
		ms_cmd_run(cmd);
	}
	return (pid);
}

void	ms_cmd_pipe(t_cmd *left, t_cmd *right)
{
	int		pid[2];
	int		fd_pipe[2];
	int		status[2];

	if (!left || !right || pipe(fd_pipe) < 0)
		ms_terminate(1, "Minishell: Pipe failed to init!\n");
	pid[0] = fork_cmd(right, fd_pipe, STDIN_FILENO);
	pid[1] = fork_cmd(left, fd_pipe, STDOUT_FILENO);
	close_fds(fd_pipe);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	ms_debug_child(pid[0], status[0]);
	ms_debug_child(pid[1], status[1]);
}
