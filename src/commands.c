/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:52:43 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/07 19:03:33 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cmd_exec(t_cmd_exec *cmd);
static void cmd_pipe(t_cmd_pipe *cmd);
static void cmd_redir(t_cmd_redir *cmd);

void	ms_cmd_run(t_cmd *cmd)
{
	//if (!cmd)
		//exit(1);
	if (cmd->type == CMD_EXEC)
		cmd_exec((t_cmd_exec *)cmd);
	if (cmd->type == CMD_REDIR)
		cmd_redir((t_cmd_redir *)cmd);
	if (cmd->type == CDM_PIPE)
		cmd_pipe((t_cmd_pipe *)cmd);
	//exit(0);
}

static void cmd_exec(t_cmd_exec *cmd)
{
	/*if (!cmd->argv)
		exit(1);*/
	//execute cmd with its arguments, should not return
	//if it returns print error message in the error output
	size_t	argi;

	argi = 0;
	printf("executing command:\n");
	while(cmd->argv[argi])
		printf("%s$\n", cmd->argv[argi++]);
	free(cmd);
}

static void cmd_pipe(t_cmd_pipe *cmd)
{
	printf("piping comands \n");
	ms_cmd_run(cmd->right);
	ms_cmd_run(cmd->left);
	free(cmd);
}

static void cmd_redir(t_cmd_redir *cmd)
{
	printf("redirection from %s to %d\n", cmd->file, cmd->fd);
	ms_cmd_run(cmd->cmd);
	free(cmd);
}
//never returns since its done on a child process

