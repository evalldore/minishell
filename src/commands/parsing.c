/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:53:23 by aroussea          #+#    #+#             */
/*   Updated: 2023/10/25 01:45:05 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_redir(t_cmd	*cmd, t_list **list);
static t_cmd	*create_redir(t_cmd *cmd, t_list **list, char *tok, char *path);

static t_cmd	*create_redir(t_cmd *cmd, t_list **list, char *tok, char *path)
{
	int		mode;

	if (tok[0] == '<')
	{
		mode = O_RDONLY;
		if (!tok[1])
			return (ms_node_redir(parse_redir(cmd, list), path, STDIN_FILENO, mode));
		else if (tok[1] == '<')
			return (parse_redir(ms_node_heredoc(cmd, path), list));
	}
	else if (tok[0] == '>')
	{
		mode = O_WRONLY | O_CREAT;
		if (!tok[1])
			mode = mode | O_TRUNC;
		else if (tok[1] == '>')
			mode = mode | O_APPEND;
		return (ms_node_redir(parse_redir(cmd, list), path, STDOUT_FILENO, mode));
	}
	return (cmd);
}

static t_cmd	*parse_redir(t_cmd	*cmd, t_list **list)
{
	t_token		*token; 
	t_token		*path;

	if (!ms_token_peek(list, TOK_REDIR))
		return (cmd);
	token = ms_token_get(list);
	path = ms_token_get(list);
	if (!path || path->type != TOK_TEXT)
		ms_terminate(1, "Minishell: No path for redirection!\n");
	return (create_redir(cmd, list, token->str, path->str));
}

static t_cmd	*parse_exec(t_list	**list)
{
	t_cmd_exec	*exec;
	t_token		*token;
	size_t		argc;

	if (!ms_token_peek(list, TOK_TEXT))
		return (NULL);
	argc = 0;
	exec = (t_cmd_exec *)ms_node_exec();
	while (ms_token_peek(list, TOK_TEXT) && argc < MAX_ARGS)
	{
		token = ms_token_get(list);
		exec->argv[argc++] = token->str;
	}
	exec->argv[argc] = NULL;
	return ((t_cmd *)exec);
}

t_cmd	*ms_cmd_parse(t_list	*list)
{
	t_cmd	*cmd;

	if (!list)
		ms_terminate(1, "Minishell: No tokens list to parse!\n");
	cmd = parse_exec(&list);
	cmd = parse_redir(cmd, &list);
	if (ms_token_peek(&list, TOK_PIPE))
	{
		ms_token_get(&list);
		cmd = ms_node_pipe(cmd, ms_cmd_parse(list));
	}
	return (cmd);
}
