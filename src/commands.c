/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:52:43 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/09 23:42:33 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cmd_exec(t_cmd_exec *cmd);
static void cmd_pipe(t_cmd_pipe *cmd);
static void cmd_redir(t_cmd_redir *cmd);

static char *find_path(char *cmd)
{
	char	*cmd_path;
	char	**paths;
	size_t	path_i;

	paths = ms_env_path();
	path_i = 0;
	while (paths[path_i])
	{
		cmd_path = ft_strjoin(paths[path_i++], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(paths);
	return (NULL);
}

void	ms_cmd_run(t_cmd *cmd)
{
	if (!cmd)
		ms_terminate(1, "Minishell: Cannot run a null command node!");
	if (cmd->type == CMD_EXEC)
		cmd_exec((t_cmd_exec *)cmd);
	if (cmd->type == CMD_REDIR)
		cmd_redir((t_cmd_redir *)cmd);
	if (cmd->type == CDM_PIPE)
		cmd_pipe((t_cmd_pipe *)cmd);
	ms_terminate(0, NULL);
}

static void cmd_exec(t_cmd_exec *cmd)
{
	char	*cmd_path;
	char	**env;

	if (!cmd)
		ms_terminate(1, "Minishell: No exec node!");
	if (!cmd->argv[0])
		ms_terminate(1, "Minishell: Exec node has no argument!");
	cmd_path = find_path(cmd->argv[0]);
	if (cmd_path)
	{
		env = ms_env_array();
		execve(cmd_path, &cmd->argv[0], env);
		free(cmd_path);
		free(env);
	}
	free(cmd);
}

static void cmd_pipe(t_cmd_pipe *cmd)
{
	int		p_id;
	int		fd_pipe[2];

	if (pipe(fd_pipe) < 0)
		exit(0);
	p_id = fork();
	if (p_id < 0)
		ms_terminate(1, "Minishell: pipe failed to init!");
	if (p_id == 0)
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		ms_cmd_run(cmd->right);
		close(fd_pipe[0]);
	}
	else
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
		ms_cmd_run(cmd->left);
		close(fd_pipe[1]);
		waitpid(p_id, NULL, 0);
	}
	free(cmd);
}

static void cmd_redir(t_cmd_redir *cmd)
{
	int	fd_redirect;

	if (cmd->fd == STDOUT_FILENO)
	{
		fd_redirect = open(cmd->file, cmd->mode, 0666);
		if (fd_redirect < 0)
			ms_terminate(1, "Minishell: Redirection file error!");
	}
	else if (cmd->fd == STDIN_FILENO)
	{
		fd_redirect = open(cmd->file, cmd->mode);
		if (fd_redirect < 0)
			ms_terminate(1, "Minishell: Redirection file error!");
	}
	if (dup2(fd_redirect, cmd->fd) < 0)
		ms_terminate(1, "Minishell: Cannot duplicate redirection file!");
	ms_cmd_run(cmd->cmd);
	free(cmd);
}
