/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/09/27 04:46:56 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	g_ms;

static void	init(char **argv, char **env)
{
	(void)argv;
	g_ms.running = true;
	g_ms.name = "\x1b[32mminishit > \x1b[0m";
	ms_token_init();
	ms_env_init(env);
	ms_env_set_var("PWD", "peepee");
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	const char		*var;

	(void)argc;
	(void)argv;
	init(argv, env);
	while (g_ms.running)
	{
		input = readline(g_ms.name);
		add_history(input);
		var = ms_env_get_var(input);
		if (var)
			printf("%s\n", var);
	}
}
