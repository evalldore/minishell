/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:20:03 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/24 02:18:39 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void write_doc(int fd, char *eof)
{
	char	*input;

	while (true)
	{
		input = readline("> ");
		if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
		{
			free(input);
			break;
		}
		ft_putstr_fd(input, fd);
		ft_putchar_fd('\n', fd);
		free(input);
	}
}

void	ms_cmd_heredoc(t_cmd *cmd, char *eof)
{
	char	*tmp_path;
	int		fd;

	if (!cmd || !eof)
		ms_terminate(1, "Minishell: Heredoc invalid parameters!\n");
	tmp_path = ft_strjoin("/tmp/", eof);
	fd = open(tmp_path, O_CREAT | O_TRUNC | O_RDWR | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		free(tmp_path);
		ms_terminate(1, "Minishell: Heredoc couldnt be created!\n");
	}
	write_doc(fd, eof);
	close(fd);
	fd = open(tmp_path, O_RDONLY | O_CLOEXEC);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
		free(tmp_path);
		ms_terminate(1, "Minishell: Heredoc invalid parameters!\n");
	}
	close(fd);
	ms_cmd_run(cmd);
}*/

void ms_heredoc_write(char *buffer, char *eof)
{
	char	*input;

	while (true)
	{
		input = readline("> ");
		if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
		{
			free(input);
			break;
		}
		ft_strlcat(buffer, input, HEREDOC_BUFFER);
		buffer[ft_strlen(buffer)] = '\n';
		free(input);
	}
}

void	ms_cmd_heredoc(char *buffer, t_cmd *cmd)
{
	int	pipe_fd[2];
	int	pid;
	int status;

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
	ft_putstr_fd(buffer, pipe_fd[1]);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	ms_debug_child(pid, status);
}

/*static void read_doc(int fd, char *eof)
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
	int status;

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
	waitpid(pid, &status, 0);
	ms_debug_child(pid, status);
}*/
