/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/03 15:39:34 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	size_t			input_len;
	char			**input_args;

	(void)argc;
	signal(SIGINT, SIG_IGN);
	init(argv, env);
	ms = ms_get();
	while (ms->running)
	{
		input = readline(PROMPT);
		input_len = ft_strlen(input);
		add_history(input);
		input_args = ft_split(input, ' ');
		if (input_args)
		{
			ms_builtin_exec(input_args);
			ms_free_array((void **)input_args);
		}
		free(input);
	}
	ms_env_clear();
	printf("exit status: %d\n", ms->status);
	return (ms->status);
}
