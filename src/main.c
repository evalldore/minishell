/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/08 23:35:52 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include "minishell.h"

static void	exec_cmd(t_minishell *ms)
{
	int				pid;
	int				status;

	ms = ms_get();
	if (ms_builtin(ms->tokens))
		return ;
	pid = fork();
	if (pid == 0)
	{
		ms->cmd = ms_cmd_parse(ms->tokens);
		ms_cmd_run(ms->cmd);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_status(WEXITSTATUS(status));
	ms_debug_child(pid, status);
}

static bool	set_var(void)
{
	t_minishell		*ms;
	t_token			*tok;
	t_var			var;

	ms = ms_get();
	if (!ms_tokens_peek(&ms->tokens, TOK_TEXT))
		return (false);
	tok = ms->tokens->content;
	if (!ms_vars_parse(&var, tok->str))
		return (false);
	if (!ms_vars_get_node(ms->env_list, var.name))
		ms_vars_set(&ms->var_list, var.name, var.value);
	else
		ms_vars_set(&ms->env_list, var.name, var.value);
	return (true);
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
		ft_lstclear(&ms->tokens, ms_tokens_del);
		input = ms_input();
		if (!input)
			continue ;
		check = 0;
		ms_tokens_init(input, &check);
		free(input);
		if (check != 0 || set_var())
			continue ;
		exec_cmd(ms);
	}
	ms_terminate(ms->status, NULL);
}
