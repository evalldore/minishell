/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:56:24 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/26 19:43:23 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_node_exec(void)
{
	t_cmd_exec	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd_exec));
	if (!cmd)
		return (NULL);
	cmd->type = CMD_EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*ms_node_heredoc(t_cmd *next, char *eof)
{
	t_cmd_heredoc	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd_heredoc));
	if (!cmd)
		return (NULL);
	cmd->type = CMD_HEREDOC;
	cmd->cmd = next;
	cmd->eof = eof;
	return ((t_cmd *)cmd);
}

t_cmd	*ms_node_pipe(t_cmd *left, t_cmd *right)
{
	t_cmd_pipe	*cmd;

	if (!left || !right)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd_pipe));
	if (!cmd)
		return (NULL);
	cmd->type = CDM_PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*ms_node_redir(t_cmd *next, char *file, int fd, int mode)
{
	t_cmd_redir	*cmd;

	if (!next || !file)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd_redir));
	if (!cmd)
		return (NULL);
	cmd->type = CMD_REDIR;
	cmd->file = file;
	cmd->fd = fd;
	cmd->mode = mode;
	cmd->cmd = next;
	return ((t_cmd *)cmd);
}
