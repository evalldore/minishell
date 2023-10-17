/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:22:40 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/15 17:14:32 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_init(char **env)
{
	t_minishell		*ms;

	ms = ms_get();
	ms->running = true;
	ms->tokens = NULL;
	ms->status = 0;
	ms->pid = -1;
	ms->pid_status = -1;
	ms->cmd = NULL;
	if (!ms_env_init(env))
	{
		ms_env_clear();
		return (false);
	}
	//signal(SIGINT, SIG_IGN);
	return (true);
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
		ft_lstclear(&ms->tokens, ms_tokens_del);
	if (ms->cmd)
		ms_cmd_free(ms->cmd);
	exit(status);
}
