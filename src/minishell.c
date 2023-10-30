/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:22:40 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/30 18:25:50 by evallee-         ###   ########.fr       */
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
	ms->cmd = NULL;
	if (!ms_env_init(env))
	{
		ms_env_clear();
		return (false);
	}
	ms->var_list = NULL;
	//signal(SIGINT, SIG_IGN);
	return (true);
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
		ms_cmd_free(ms->cmd);
	exit(status);
}