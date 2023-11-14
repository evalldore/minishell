/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:53:23 by aroussea          #+#    #+#             */
/*   Updated: 2023/11/14 15:47:27 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_redir(t_cmd	*cmd, t_list **list);

static t_cmd	*create_redir(t_cmd *cmd, t_list **list, char *tok, char *path)
{
	int		mode;
	int		std;

	if (tok[0] == '<')
	{
		std = STDIN_FILENO;
		mode = O_RDONLY;
		if (!tok[1])
			return (ms_node_redir(parse_redir(cmd, list), path, std, mode));
		else if (tok[1] == '<')
			return (ms_node_heredoc(parse_redir(cmd, list), path));
	}
	else if (tok[0] == '>')
	{
		std = STDOUT_FILENO;
		mode = O_WRONLY | O_CREAT;
		if (!tok[1])
			mode = mode | O_TRUNC;
		else if (tok[1] == '>')
			mode = mode | O_APPEND;
		return (ms_node_redir(parse_redir(cmd, list), path, std, mode));
	}
	return (cmd);
}

static t_cmd	*parse_redir(t_cmd	*cmd, t_list **list)
{
	t_token		*token; 
	t_token		*path;

	if (!ms_tokens_peek(list, TOK_REDIR))
		return (cmd);
	token = ms_tokens_get(list);
	path = ms_tokens_get(list);
	if (!path || path->type != TOK_TEXT)
		ms_terminate(1, "Minishell: No path for redirection!\n");
	return (create_redir(cmd, list, token->str, path->str));
}

static t_cmd	*parse_exec(t_list	**list)
{
	t_cmd		*cmd;
	t_cmd_exec	*exec;
	t_token		*token;

	cmd = ms_node_exec();
	exec = (t_cmd_exec *)cmd;
	cmd = parse_redir(cmd, list);
	while (ms_tokens_peek(list, TOK_TEXT))
	{
		token = ms_tokens_get(list);
		exec->argv[exec->argc] = token->str;
		exec->argc++;
		if (exec->argc >= (MAX_ARGS - 1))
			break ;
		cmd = parse_redir(cmd, list);
	}
	exec->argv[exec->argc] = NULL;
	return (cmd);
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
	ms_signal_set(MODE_HEREDOC);
	write_heredocs(cmd);
	ms_signal_set(MODE_MAIN);
	if (ms_tokens_peek(&list, TOK_PIPE))
	{
		ms_tokens_get(&list);
		if (cmd->type == CMD_EXEC && !((t_cmd_exec *)cmd)->argv[0])
			ms_terminate(1, "Minishell: Pipe invalid command!\n");
		cmd = ms_node_pipe(cmd, ms_cmd_parse(list));
	}
	return (cmd);
}
