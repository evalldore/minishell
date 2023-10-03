/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/03 02:03:41 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(char **argv, char **env)
{
	t_minishell		*ms;

	(void)argv;
	ms = ms_get();
	ms->running = true;
	ms_token_init();
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
	const char		*var;
	t_minishell		*ms;
	size_t			input_len;

	(void)argc;
	signal(SIGQUIT, SIG_IGN);
	init(argv, env);
	ms = ms_get();
	while (ms->running)
	{
		input = readline(PROMPT);
		input_len = ft_strlen(input);
		add_history(input);
		var = ms_env_get_var(input);
		if (var)
			printf("%s\n", var);
		else
		{
			if (ft_strncmp(input, "pwd", input_len) == 0)
				ms_builtin_pwd();
			if (ft_strncmp(input, "exit", input_len) == 0)
				ms_builtin_exit(0);
		}
		free(input);
	}
	ms_env_clear();
	return (ms->status);
}
