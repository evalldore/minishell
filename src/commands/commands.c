/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:52:43 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/13 19:51:44 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_exec(t_cmd_exec *cmd);
static void	cmd_redir(t_cmd_redir *cmd);

void	ms_cmd_run(t_cmd *cmd)
{
	t_cmd_pipe		*cmd_pipe;
	t_cmd_heredoc	*cmd_heredoc;

	if (!cmd)
		ms_terminate(1, "Minishell: Command node is null!\n");
	if (cmd->type == CMD_EXEC)
		cmd_exec((t_cmd_exec *)cmd);
	else if (cmd->type == CMD_REDIR)
		cmd_redir((t_cmd_redir *)cmd);
	else if (cmd->type == CDM_PIPE)
	{
		cmd_pipe = (t_cmd_pipe *)cmd;
		ms_cmd_pipe(cmd_pipe->left, cmd_pipe->right);
	}
	else if (cmd->type == CMD_HEREDOC)
	{
		cmd_heredoc = (t_cmd_heredoc *)cmd;
		ms_cmd_heredoc(cmd_heredoc->buffer, cmd_heredoc->cmd);
	}
	ms_terminate(0, NULL);
}

static void	run_bin(char *path, char **argv)
{
	int			pid;
	int			status;
	char		**env;

	pid = fork();
	if (pid == -1)
		ms_terminate(1, "Minishell: Fork binary failed\n");
	if (pid == 0)
	{
		env = ms_env_array();
		execve(path, argv, env);
		free(env);
		ms_terminate(1, "Minishell: Command failed to run!\n");
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (ms_terminate(WEXITSTATUS(status), NULL));
	ms_terminate(1, NULL);
}

static void	cmd_exec(t_cmd_exec *cmd)
{
	char		*cmd_path;

	if (!cmd->argv[0])
		ms_terminate(1, "Minishell: Exec node has no argument!\n");
	if (ms_builtin_exec(cmd->argc, &cmd->argv[0]))
		return ;
	if (access(cmd->argv[0], F_OK | X_OK) == 0)
		run_bin(cmd->argv[0], cmd->argv);
	cmd_path = ms_path_find(cmd->argv[0]);
	if (cmd_path)
	{
		run_bin(cmd_path, cmd->argv);
		free(cmd_path);
	}
	ms_terminate(127, "Minishell: Command doesnt exist!\n");
}

static void	cmd_redir(t_cmd_redir *cmd)
{
	int			fd_redirect;

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
	close(fd_redirect);
	ms_cmd_run(cmd->cmd);
}
