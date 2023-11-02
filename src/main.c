/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/01 22:36:30 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include "minishell.h"

static void	exec_cmd(void)
{
	t_minishell		*ms;
	t_cmd_exec		*cmd_exec;
	int				pid;
	int				status;

	ms = ms_get();
	ms->cmd = ms_cmd_parse(ms->tokens);
	if (ms->cmd->type == CMD_EXEC)
	{
		cmd_exec = (t_cmd_exec *)ms->cmd;
		if (ms_builtin_exec(cmd_exec->argc, cmd_exec->argv))
		{
			ms_cmd_free(ms->cmd);
			ms->cmd = NULL;
			return ;
		}
	}
	pid = fork();
	if (pid == 0)
		ms_cmd_run(ms->cmd);
	waitpid(pid, &status, 0);
	ms_vars_set(&ms->var_list, "?", ft_itoa(status));
	ms_debug_child(pid, status);
}

static bool	set_var(void)
{
	t_minishell		*ms;
	t_token			*tok;
	char			var_name[VARNAME_BUFFER];
	char			var[VAR_BUFFER];

	ms = ms_get();
	if (!ms_tokens_peek(&ms->tokens, TOK_TEXT))
		return (false);
	tok = ms->tokens->content;
	if (!ft_strchr(tok->str, '='))
		return (false);
	ft_memset(var_name, 0, VARNAME_BUFFER);
	ft_memset(var, 0, VAR_BUFFER);
	ft_strlcpy(var_name, tok->str, (ft_strchr(tok->str, '=') - tok->str) + 1);
	ft_strlcpy(var, ft_strchr(tok->str, '=') + 1, VAR_BUFFER);
	if (!var_name[0] || !var[0])
		return (false);
	if (!ms_vars_get_node(ms->env_list, var_name))
		ms_vars_set(&ms->var_list, var_name, var);
	else
		ms_vars_set(&ms->env_list, var_name, var);
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
		input = ms_input();
		if (!input)
			continue ;
		check = 0;
		ms_tokens_init(input, &check);
		free(input);
		if (check != 0 || set_var())
		{
			ft_lstclear(&ms->tokens, ms_tokens_del);
			continue ;
		}
		exec_cmd();
		ft_lstclear(&ms->tokens, ms_tokens_del);
	}
	printf("exit status: %d\n", ms->status);
	ms_terminate(ms->status, NULL);
}
