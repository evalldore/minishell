/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:53:23 by aroussea          #+#    #+#             */
/*   Updated: 2023/10/08 19:21:43 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*list_get(t_list **list)
{
	t_token		*token;

	if (!(*list))
		return (NULL);
	token = (*list)->content;
	*list = (*list)->next;
	return (token);
}

static bool		list_peek(t_list **list, int type)
{
	t_token		*token;

	if (!*list)
		return (false);
	token = (*list)->content;
	return (token->type == type);
}

static t_cmd	*parse_redir(t_cmd	*cmd, t_list **list)
{
	t_token		*token;
	char		*path;

	if (list_peek(list, TOK_REDIR))
	{
		token = list_get(list);
		path = list_get(list)->str;
		if (list_get(list)->type != TOK_TEXT)
			ms_terminate(1, "Minishell: Missing file for redirection!\n");
		if (token->str[0] == '<')
			return (ms_node_redir(cmd, path, 1));
		if (token->str[0] == '>')
			return (ms_node_redir(cmd, path, 0));
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
	while (!list_peek(list, TOK_PIPE))
	{
		token = list_get(list);
		if (!token || token->type == TOK_NONE)
			break;
		if (token->type != TOK_TEXT)
			ms_terminate(1, "Minishell: Syntax error\n");
		exec->argv[argc] = token->str;
		argc++;
		if(argc >= MAX_ARGS)
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
	if (list_peek(&list, TOK_PIPE))
	{
		list_get(&list);
		cmd = ms_node_pipe(cmd, ms_cmd_parse(list));
	}
	return (cmd);
}


