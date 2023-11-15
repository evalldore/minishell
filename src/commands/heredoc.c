/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:20:03 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/15 15:17:42 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_input(void)
{
	char	*input;

	input = readline("> ");
	if (!input)
	{
		ft_putstr_fd("Closed heredoc\n", 2);
		return (NULL);
	}
	input = check_expand(input);
	return (input);
}

static bool	is_delim(char *input, char *delim)
{
	size_t	i;

	if (!input || !delim)
		return (false);
	i = 0;
	while (delim[i])
	{
		if (delim[i] != input[i])
			return (false);
		i++;
	}
	return (true);
}

void	ms_heredoc_write(char *buffer, char *eof)
{
	char	*input;
	size_t	input_len;
	size_t	buffer_len;

	while (true)
	{
		input = heredoc_input();
		if (!input)
			return ;
		input_len = ft_strlen(input);
		buffer_len = ft_strlen(buffer);
		if (is_delim(input, eof))
			return (free(input));
		if ((buffer_len + input_len + 1) >= HEREDOC_BUFFER)
		{
			free(input);
			ms_terminate(1, "Minishell: Too much crap in heredoc, fuck you!\n");
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
	int	status;

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
