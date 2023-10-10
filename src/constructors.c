/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:56:24 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/09 19:32:26 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_node_exec(void)
{
	t_cmd_exec	*cmd;

	cmd = malloc(sizeof(t_cmd_exec));
	if (!cmd)
		return (NULL);
	memset(cmd, 0, sizeof(t_cmd_exec));
	cmd->type = CMD_EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*ms_node_pipe(t_cmd *left, t_cmd *right)
{
	t_cmd_pipe	*cmd;

	cmd = malloc(sizeof(t_cmd_pipe));
	if (!cmd)
		return (NULL);
	memset(cmd, 0, sizeof(t_cmd_pipe)); 
	cmd->type = CDM_PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*ms_node_redir(t_cmd *next, char *file, int fd)
{
	t_cmd_redir	*cmd;
	int			mode;

	cmd = malloc(sizeof(t_cmd_redir));
	if (!cmd)
		return (NULL);
	memset(cmd, 0, sizeof(t_cmd_redir));
	mode = O_WRONLY|O_CREAT|O_TRUNC;
	if (fd == STDIN_FILENO)
		mode = O_RDONLY;
	cmd->type = CMD_REDIR;
	cmd->file = file;
	cmd->fd = fd;
	cmd->mode = mode;
	cmd->cmd = next;
	return ((t_cmd *)cmd);
}
