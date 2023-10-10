/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/10 17:26:40 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include "minishell.h"

static void	init(char **argv, char **env)
{
	t_minishell		*ms;

	(void)argv;
	ms = ms_get();
	ms->input = NULL;
	ms->running = true;
	ms->tokens = NULL;
	ms->status = 0;
	ms->pid = -1;
	ms->pid_status = -1;
	ms_env_init(env);
}

t_minishell	*ms_get(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		*ms;

	(void)argc;
	//signal(SIGINT, SIG_IGN);
	init(argv, env);
	ms = ms_get();
	while (ms->running)
	{
		ms->input = readline(PROMPT);
		if (!ms->input || !(*ms->input))
		{
			free(ms->input);
			continue ;
		}
		add_history(ms->input);
		ms_tokens_init(ms->input);
		ms->pid = fork();
		if (ms->pid == 0)
			ms_cmd_run(ms_cmd_parse(ms->tokens));
		else
		{
			waitpid(ms->pid, &ms->pid_status, 0);
			ms_debug_child(ms->pid, ms->pid_status);
			free(ms->input);
			ft_lstclear(&ms->tokens, free);
		}
	}
	printf("exit status: %d\n", ms->status);
	ms_terminate(ms->status, NULL);
}
