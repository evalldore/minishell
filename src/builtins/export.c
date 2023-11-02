/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:58:57 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/01 23:18:45 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void transfer_top(t_list *node)
{
	ms_get()->var_list = node->next;
	node->next = NULL;
	ft_lstadd_back(&(ms_get()->env_list), node);
}

void	ms_builtin_export(const char *str)
{
	t_list			*node;
	t_list			*list;

	if (!str)
		return ;
	list = ms_get()->var_list;
	node = ms_vars_get_node(list, str);
	if (!list || !node)
		return ;
	if (list == node)
		return transfer_top(node);
	while (list)
	{
		if (list->next == node)
		{
			list->next = node->next;
			node->next = NULL;
			ft_lstadd_back(&(ms_get()->env_list), node);
			return ;
		}
		list = list->next;
	}
}
