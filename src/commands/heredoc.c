/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:20:03 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/17 23:10:20 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

		ms_terminate(1, "Minishell: Redirection node is null!\n");
	fd_redirect = -1;
	if (cmd->fd == STDOUT_FILENO)
		fd_redirect = open(cmd->file, cmd->mode | O_CLOEXEC, 0666);
	else if (cmd->fd == STDIN_FILENO)
		fd_redirect = open(cmd->file, cmd->mode | O_CLOEXEC);
	if (fd_redirect < 0)
		ms_terminate(1, "Minishell: Redirection file error!\n");
	if (dup2(fd_redirect, cmd->fd) < 0)
	{
		close(fd_redirect);
		ms_terminate(1, "Minishell: Cannot duplicate redirection file!\n");
	}
	ms_cmd_run(cmd->cmd);

*/

static void read_doc(int fd, char *eof)
{
	char	*input;
	char	buffer[1024];

	ft_memset(buffer, 0, sizeof(buffer));
	while (true)
	{
		input = readline("> ");
		if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
		{
			free(input);
			break;
		}
		ft_strlcat(buffer, input, 1024);
		buffer[ft_strlen(buffer)] = '\n';
		free(input);
	}
	ft_putstr_fd(buffer, fd);
}

void	ms_cmd_heredoc(t_cmd *cmd, char *eof)
{
	int	pipe_fd[2];
	int	pid;

	if (!cmd || !eof)
		ms_terminate(1, "Minishell: Heredoc invalid parameters!\n");
	if (pipe(pipe_fd) != 0)
		ms_terminate(1, "Minishell: Heredoc pipe failed!\n");
	pid = fork();
	if (pid < 0)
		ms_terminate(1, "Minishell: Heredoc child proccess issue!\n");
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		ms_cmd_run(cmd);
	}
	close(pipe_fd[0]);
	read_doc(pipe_fd[1], eof);
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
}
