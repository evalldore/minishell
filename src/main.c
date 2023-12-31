/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/16 16:26:38 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_minishell *ms)
{
	int				pid;
	int				status;

	ms = ms_get();
	if (ms_builtin(ms->tokens))
		return ;
	ms_signal_set(MODE_IGN);
	pid = fork();
	if (pid == -1)
		ms_terminate(1, "Minishell: Couldnt fork command process!\n");
	if (pid == 0)
	{
		ms_signal_set(MODE_MAIN);
		ms->cmd = ms_cmd_parse(ms->tokens);
		ms_cmd_run(ms->cmd);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		ms_status(WTERMSIG(status) + 128);
	}
	ms_debug_child(pid, status);
}

static bool	set_var(t_list	*tokens)
{
	t_minishell		*ms;
	t_token			*tok;
	t_var			var;

	ms = ms_get();
	if (!tokens || !ms_tokens_peek(&tokens, TOK_TEXT))
		return (false);
	tok = tokens->content;
	if (!ms_vars_parse(&var, tok->str))
		return (false);
	if (!ms_vars_get_node(ms->env_list, var.name))
		ms_vars_set(&ms->var_list, var.name, var.value);
	else
		ms_vars_set(&ms->env_list, var.name, var.value);
	set_var(tokens->next);
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
		ms_signal_set(MODE_DEFAULT);
		ft_lstclear(&ms->tokens, ms_tokens_del);
		input = ms_input();
		if (!input)
			continue ;
		check = 0;
		ms_tokens_init(input, &check);
		free(input);
		if (check != 0 || set_var(ms->tokens))
			continue ;
		exec_cmd(ms);
	}
	ms_terminate(ms->status, NULL);
}
