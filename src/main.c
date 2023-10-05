/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/05 00:33:56 by niceguy          ###   ########.fr       */
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
	ms_env_init(env);
}

t_minishell	*ms_get(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_minishell		*ms;
	char			**input_args;

	(void)argc;
	signal(SIGINT, SIG_IGN);
	init(argv, env);
	ms = ms_get();
	while (ms->running)
	{
		printf("%s%s%s:", COLOR_CYAN, ms_env_get_var("PWD"), COLOR_RESET);
		input = readline(PROMPT);
		add_history(input);
		ms_token_init(input);
		input_args = ft_split(input, ' ');
		if (input_args)
		{
			ms_builtin_exec(ms_array_count((void **)input_args), input_args);
			ms_array_free((void **)input_args);
		}
		free(input);
	}
	ms_env_clear();
	printf("exit status: %d\n", ms->status);
	return (ms->status);
}
