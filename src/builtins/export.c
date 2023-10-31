/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:58:57 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/31 02:18:36 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_export(const char *str)
{
	t_list			*node;
	t_list			*list;
	t_list			*last;

	if (!str)
		return ;
	list = ms_get()->var_list;
	node = ms_vars_get_node(list, str);
	if (!list || !node)
		return ;
	last = list;
	while (list)
	{
		if (list == node)
		{
			list->next = node->next;
			node->next = NULL;
			ft_lstadd_back(&(ms_get()->env_list), node);
			return ;
		}
		list = list->next;
	}
}
