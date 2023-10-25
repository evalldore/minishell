/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:53:23 by aroussea          #+#    #+#             */
/*   Updated: 2023/10/25 19:26:07 by niceguy          ###   ########.fr       */
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
			return (ms_node_heredoc(parse_redir(cmd, list), path));
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

static void	write_heredocs(t_cmd *cmd)
{
	t_cmd_heredoc	*cmd_heredoc;
	t_cmd_redir		*cmd_redir;

	if (!cmd)
		return ;
	if (cmd->type != CMD_REDIR && cmd->type != CMD_HEREDOC)
		return ;
	if (cmd->type == CMD_HEREDOC)
	{
		cmd_heredoc = (t_cmd_heredoc *)cmd;
		ms_heredoc_write(cmd_heredoc->buffer, cmd_heredoc->eof);
		write_heredocs(cmd_heredoc->cmd);
		return ;
	}
	cmd_redir = (t_cmd_redir *)cmd;
	write_heredocs(cmd_redir->cmd);
}

t_cmd	*ms_cmd_parse(t_list	*list)
{
	t_cmd	*cmd;

	if (!list)
		ms_terminate(1, "Minishell: No tokens list to parse!\n");
	cmd = parse_exec(&list);
	cmd = parse_redir(cmd, &list);
	write_heredocs(cmd);
	if (ms_token_peek(&list, TOK_PIPE))
	{
		ms_token_get(&list);
		cmd = ms_node_pipe(cmd, ms_cmd_parse(list));
	}
	return (cmd);
}
