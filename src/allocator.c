/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:41:55 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/12 14:31:52 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_allocator	*get_alloc()
{
	static t_allocator	alloc;

	return (&alloc);
}

void	ms_alloc_reset(void)
{
	t_allocator		*alloc;
	uint32_t		i;

	i = 0;
	while (i < MAX_NODE)
		alloc->index[i++] = 0; 
}

t_cmd	*ms_alloc_node(int type)
{
	t_allocator		*alloc;
	uint32_t		index;
	t_cmd			*cmd;

	if (type >= MAX_NODE)
		return (NULL);
	alloc = get_alloc();
	index = alloc->index[type];
	if (type == CMD_EXEC)
		cmd = (t_cmd *)(&alloc->exec[index]);
	else if (type == CDM_PIPE)
		cmd = (t_cmd *)(&alloc->pipe[index]);
	else if (type == CMD_REDIR)
		cmd = (t_cmd *)(&alloc->redir[index]);
	alloc->index[type]++;
	return (cmd);
}
