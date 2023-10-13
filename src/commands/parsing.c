/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:53:23 by aroussea          #+#    #+#             */
/*   Updated: 2023/10/12 22:42:08 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_redir(t_cmd	*cmd, t_list **list)
{
	t_token		*token;
	t_token		*path;
	int			mode;

	if (ms_token_peek(list, TOK_REDIR))
	{
		token = ms_token_get(list);
		path = ms_token_get(list);
		if (!path || path->type != TOK_TEXT)
			ms_terminate(1, "Minishell: Missing file for redirection!\n");
		if (token->str[0] == '<')
			return (ms_node_redir(cmd, path->str, STDIN_FILENO, O_RDONLY));
		if (token->str[0] == '>')
		{
			mode = O_WRONLY | O_CREAT;
			if (!token->str[1])
				mode = mode | O_TRUNC;
			else if (token->str[1] == '>')
				mode = mode | O_APPEND;
			return (ms_node_redir(cmd, path->str, STDOUT_FILENO, mode));
		}
	}
	return (cmd);
}

static t_cmd	*parse_exec(t_list	**list)
{
	t_cmd		*cmd;
	t_cmd_exec	*exec;
	t_token		*token;
	size_t		argc;

	exec = (t_cmd_exec *)ms_node_exec();
	cmd = parse_redir((t_cmd *)exec, list);
	argc = 0;
	while (!ms_token_peek(list, TOK_PIPE))
	{
		token = ms_token_get(list);
		if (!token || token->type == TOK_NONE)
			break ;
		if (token->type != TOK_TEXT)
			ms_terminate(1, "Minishell: Syntax error\n");
		exec->argv[argc++] = token->str;
		if (argc >= MAX_ARGS)
			ms_terminate(1, "Minishell: Too many arguments!\n");
		cmd = parse_redir(cmd, list);
	}
	exec->argv[argc] = NULL;
	return (cmd);
}

t_cmd	*ms_cmd_parse(t_list	*list)
{
	t_cmd	*cmd;

	cmd = parse_exec(&list);
	if (ms_token_peek(&list, TOK_PIPE))
	{
		ms_token_get(&list);
		cmd = ms_node_pipe(cmd, ms_cmd_parse(list));
	}
	return (cmd);
}
