/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:53:23 by aroussea          #+#    #+#             */
/*   Updated: 2023/10/07 18:51:06 by niceguy          ###   ########.fr       */
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
		/*if (!list_get(list)->type == TOK_TEXT)
			exit(1);*/
		if (token->str[0] == '<')
			return (ms_node_redir(cmd, ft_strdup(path), 1));
		if (token->str[0] == '>')
			return (ms_node_redir(cmd, ft_strdup(path), 0));
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
		/*if (token->type != TOK_TEXT)
			exit(1);*/
		exec->argv[argc] = ft_strdup(token->str);
		argc++;
		/*if(argc >= MAX_ARGS)
			exit(1);*/
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


