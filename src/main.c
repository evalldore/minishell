/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/09 23:56:37 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include "minishell.h"

static void	init(char **argv, char **env)
{
	t_minishell		*ms;

	(void)argv;
	ms = ms_get();
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

/*/static void print_token(void *p)
{
	t_token		*token;

	token = p;
	printf("%s:%d\n", token->str, token->type);
}*/

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_minishell		*ms;

	(void)argc;
	//signal(SIGINT, SIG_IGN);
	init(argv, env);
	ms = ms_get();
	while (ms->running)
	{
		//printf("%s%s%s:", COLOR_CYAN, ms_env_get_var("PWD"), COLOR_RESET);
		input = readline(PROMPT);
		add_history(input);
		ms_tokens_init(input);
		//ft_lstiter(tokens, print_token);
		ms->pid = fork();
		if (ms->pid == 0)
			ms_cmd_run(ms_cmd_parse(ms->tokens));
		waitpid(ms->pid, &ms->pid_status, 0);
		if (WIFEXITED(ms->pid_status))
			printf("Child process (PID %d) exited with status: %d\n", ms->pid, WEXITSTATUS(ms->pid_status));
		else
			printf("Child process did not exit normally.\n");
		free(input);
		ft_lstclear(&ms->tokens, free);
	}
	printf("exit status: %d\n", ms->status);
	ms_terminate(ms->status, NULL);
}
