/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:53:23 by aroussea          #+#    #+#             */
/*   Updated: 2023/10/17 19:48:43 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*redir_out(t_cmd *cmd, char *tok_str, char *path_str)
{
	int		mode;

	mode = O_WRONLY | O_CREAT;
	if (!tok_str[1])
		mode = mode | O_TRUNC;
	else if (tok_str[1] == '>')
		mode = mode | O_APPEND;
	return (ms_node_redir(cmd, path_str, STDOUT_FILENO, mode));
}

static t_cmd	*redir_in(t_cmd	*cmd, char *tok_str, char *path_str)
{
	int		mode;

	mode = O_RDONLY;
	if (!tok_str[1])
		return (ms_node_redir(cmd, path_str, STDIN_FILENO, mode));
	else if (tok_str[1] == '<')
		return (ms_node_heredoc(cmd, path_str));
	return (NULL);
}

static t_cmd	*parse_redir(t_cmd	*cmd, t_list **list)
{
	t_token		*token;
	t_token		*path;

	if (!cmd || !list)
		ms_terminate(1, "Minishell: Cannot parsing a redirection!\n");
	if (ms_token_peek(list, TOK_REDIR))
	{
		token = ms_token_get(list);
		path = ms_token_get(list);
		if (!path || path->type != TOK_TEXT)
			ms_terminate(1, "Minishell: Missing file for redirection!\n");
		if (token->str[0] == '<')
			return (redir_in(cmd, token->str, path->str));
		if (token->str[0] == '>')
			return (redir_out(cmd, token->str, path->str));
	}
	return (cmd);
}

static t_cmd	*parse_exec(t_list	**list)
{
	t_cmd		*cmd;
	t_cmd_exec	*exec;
	t_token		*token;
	size_t		argc;

	if (!list)
		ms_terminate(1, "Minishell: Tokens list is null!\n");
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

	if (!list)
		ms_terminate(1, "Minishell: Tokens list is null!\n");
	cmd = parse_exec(&list);
	if (ms_token_peek(&list, TOK_PIPE))
	{
		ms_token_get(&list);
		cmd = ms_node_pipe(cmd, ms_cmd_parse(list));
	}
	return (cmd);
}
