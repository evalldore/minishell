/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:55:10 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/12 03:34:57 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_free(t_cmd *cmd)
{
	t_cmd_pipe	*cmd_pipe;
	t_cmd_redir	*cmd_redir;

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
	else if (cmd->type == CMD_EXEC)
		free(cmd);
}

int	ms_terminate(int status, char	*msg)
{
	t_minishell		*ms;

	ms = ms_get();
	if (msg)
		ft_putstr_fd(msg, 2);
	ms_env_clear();
	if (ms->tokens)
		ft_lstclear(&ms->tokens, free);
	if (ms->cmd)
		ms_cmd_free(ms->cmd);
	exit(status);
}

void	ms_array_free(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

size_t	ms_array_count(void **array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
