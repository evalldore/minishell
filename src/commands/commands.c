/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:52:43 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/24 02:13:57 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_exec(t_cmd_exec *cmd);
static void	cmd_pipe(t_cmd_pipe *cmd);
static void	cmd_redir(t_cmd_redir *cmd);
static void cmd_heredoc(t_cmd_heredoc *cmd);

static void cmd_heredoc(t_cmd_heredoc *cmd)
{
	if (!cmd)
		ms_terminate(1, "Minishell: Heredoc node is null!\n");
	ms_cmd_heredoc(cmd->buffer, cmd->cmd);
}

void	ms_cmd_run(t_cmd *cmd)
{
	if (!cmd)
		ms_terminate(1, "Minishell: Command node is null!\n");
	if (cmd->type == CMD_EXEC)
		cmd_exec((t_cmd_exec *)cmd);
	if (cmd->type == CMD_REDIR)
		cmd_redir((t_cmd_redir *)cmd);
	if (cmd->type == CDM_PIPE)
		cmd_pipe((t_cmd_pipe *)cmd);
	if (cmd->type == CMD_HEREDOC)
		cmd_heredoc((t_cmd_heredoc *)cmd);
	ms_terminate(0, NULL);
}

static void	cmd_exec(t_cmd_exec *cmd)
{
	char		*cmd_path;
	char		**env;

	if (!cmd->argv[0])
		ms_terminate(1, "Minishell: Exec node has no argument!\n");
	cmd_path = ms_find_path(cmd->argv[0]);
	if (cmd_path)
	{
		env = ms_env_array();
		execve(cmd_path, &cmd->argv[0], env);
		free(cmd_path);
		free(env);
		ms_terminate(1, "Minishell: Command failed to run!\n");
	}
	ms_terminate(127, "Minishell: Command doesnt exist!\n");
}

static void	cmd_pipe(t_cmd_pipe *cmd)
{
	ms_cmd_pipe(cmd->left, cmd->right);
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
