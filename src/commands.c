/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:52:43 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/09 00:26:06 by niceguy          ###   ########.fr       */
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
	printf("piping comands \n");
	ms_cmd_run(cmd->right);
	ms_cmd_run(cmd->left);
	free(cmd);
}

static void cmd_redir(t_cmd_redir *cmd)
{
	printf("redirection from %s to %d\n", cmd->file, cmd->fd);
	ms_cmd_run(cmd->cmd);
	free(cmd);
}
