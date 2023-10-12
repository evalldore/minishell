/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:41:55 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/12 01:59:34 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_alloc_node(int type)
{
	static t_allocator	alloc;
	uint32_t			index;
	t_cmd				*cmd;

	if (type >= MAX_NODE)
		return (NULL);
	index = alloc.index[type];
	if (type == CMD_EXEC)
		cmd = (t_cmd *)(&alloc.exec[index]);
	else if (type == CDM_PIPE)
		cmd = (t_cmd *)(&alloc.pipe[index]);
	else if (type == CMD_REDIR)
		cmd = (t_cmd *)(&alloc.redir[index]);
	alloc.index[type]++;
	return (cmd);
}
