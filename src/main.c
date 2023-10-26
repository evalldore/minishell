/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/26 16:56:19 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include "minishell.h"

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
	int				check;

	(void)argc;
	(void)argv;
	if (!ms_init(env))
		return (EXIT_FAILURE);
	ms = ms_get();
	while (ms->running)
	{
		input = ms_input();
		if (!input)
			continue ;
		check = 0;
		ms_tokens_init(input, &check);
		free(input);
		if (check != 0)
		{
			ft_lstclear(&ms->tokens, ms_tokens_del);
			continue ;
		}
		fork_cmd();
		ft_lstclear(&ms->tokens, ms_tokens_del);
	}
	printf("exit status: %d\n", ms->status);
	ms_terminate(ms->status, NULL);
}
