/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/12 22:27:03 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include "minishell.h"

static bool	init(char **argv, char **env)
{
	t_minishell		*ms;

	(void)argv;
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

static void	fork_cmd(void)
{
	t_minishell		*ms;

	ms = ms_get();
	ms->pid = fork();
	if (ms->pid == 0)
	{
		ms->cmd = ms_cmd_parse(ms->tokens);
		ms_cmd_run(ms->cmd);
	}
	waitpid(ms->pid, &ms->pid_status, 0);
	ms_debug_child(ms->pid, ms->pid_status);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		*ms;
	char			*input;

	(void)argc;
	if (!init(argv, env))
		return (EXIT_FAILURE);
	ms = ms_get();
	while (ms->running)
	{
		input = readline(PROMPT);
		if (!input || !(*input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		ms_tokens_init(input);
		free(input);
		fork_cmd();
		ft_lstclear(&ms->tokens, free);
	}
	printf("exit status: %d\n", ms->status);
	ms_terminate(ms->status, NULL);
}
