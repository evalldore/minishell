/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:22:40 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/02 22:41:18 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_init(char **env)
{
	t_minishell		*ms;

	ms = ms_get();
	ms->running = true;
	ms->tokens = NULL;
	ms->cmd = NULL;
	if (!ms_env_init(env))
	{
		ms_env_clear();
		return (false);
	}
	ms->var_list = NULL;
	ms_status(0);
	//signal(SIGINT, SIG_IGN);
	return (true);
}

void	ms_status(int status)
{
	t_minishell		*ms;
	char			*status_str;

	ms = ms_get();
	ms->status = status;
	status_str = ft_itoa(status);
	ms_vars_set(&ms->var_list, "?", status_str);
	free(status_str);
}

char	*ms_input(void)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
		return (NULL);
	if (!input[0])
	{
		free(input);
		return (NULL);
	}
	add_history(input);
	return (input);
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
		ms_cmd_free(&ms->cmd);
	exit(status);
}
