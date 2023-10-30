/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/29 16:46:00 by niceguy          ###   ########.fr       */
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
	ms_env_set_var("?", ft_itoa(status));
	ms_debug_child(pid, status);
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
		exec_cmd();
		ft_lstclear(&ms->tokens, ms_tokens_del);
	}
	printf("exit status: %d\n", ms->status);
	ms_terminate(ms->status, NULL);
}
