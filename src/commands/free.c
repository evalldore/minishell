/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:58:11 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/25 15:31:13 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_free(t_cmd *cmd)
{
	t_cmd_pipe		*cmd_pipe;
	t_cmd_redir		*cmd_redir;
	t_cmd_heredoc	*cmd_heredoc;

	if (!cmd)
		return ;
	if (cmd->type == CDM_PIPE)
	{
		cmd_pipe = (t_cmd_pipe *)cmd;
		ms_cmd_free(cmd_pipe->left);
		ms_cmd_free(cmd_pipe->right);
	}
	else if (cmd->type == CMD_REDIR)
	{
		cmd_redir = (t_cmd_redir *)cmd;
		ms_cmd_free(cmd_redir->cmd);
	}
	else if (cmd->type == CMD_HEREDOC)
	{
		cmd_heredoc = (t_cmd_heredoc *)cmd;
		ms_cmd_free(cmd_heredoc->cmd);
	}
	else if (cmd->type == CMD_EXEC)
		free(cmd);
}
