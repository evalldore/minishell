/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:22:40 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/12 22:25:07 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_free(t_cmd *cmd)
{
	t_cmd_pipe	*cmd_pipe;
	t_cmd_redir	*cmd_redir;

	if (cmd->type == CDM_PIPE)
	{
		cmd_pipe = (t_cmd_pipe *)cmd;
		cmd_free(cmd_pipe->left);
		cmd_free(cmd_pipe->right);
	}
	else if (cmd->type == CMD_REDIR)
	{
		cmd_redir = (t_cmd_redir *)cmd;
		cmd_free(cmd_redir->cmd);
	}
	else if (cmd->type == CMD_EXEC)
		free(cmd);
}

t_minishell	*ms_get(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

void	ms_terminate(int status, char	*msg)
{
	t_minishell		*ms;

	ms = ms_get();
	if (msg)
		ft_putstr_fd(msg, 2);
	ms_env_clear();
	if (ms->tokens)
		ft_lstclear(&ms->tokens, free);
	if (ms->cmd)
		cmd_free(ms->cmd);
	exit(status);
}