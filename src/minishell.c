/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:22:40 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/14 15:21:06 by evallee-         ###   ########.fr       */
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
		ft_lstclear(&ms->env_list, free);
		return (false);
	}
	ms->var_list = NULL;
	ms_status(0);
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
		ms_terminate(0, "exit\n");
	if (!*input)
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
	ft_lstclear(&ms->env_list, free);
	ft_lstclear(&ms->var_list, free);
	ft_lstclear(&ms->tokens, ms_tokens_del);
	if (ms->cmd)
		ms_cmd_free(&ms->cmd);
	exit(status);
}
