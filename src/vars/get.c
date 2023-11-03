/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 02:38:37 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/02 17:39:32 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_var(const char *arg, const char *env)
{
	uint32_t	i;

	if (!arg || !env)
		return (false);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=' && !arg[i])
			return (true);
		if (env[i] != arg[i])
			return (false);
		i++;
	}
	return (false);
}

t_list	*ms_vars_get_node(t_list *list, const char *arg)
{
	if (!list || !arg)
		return (NULL);
	while (list)
	{
		if (check_var(arg, list->content))
			return (list);
		list = list->next;
	}
	return (NULL);
}

char	*ms_vars_get_var(t_list *list, const char *arg)
{
	t_list	*node;

	node = ms_vars_get_node(list, arg);
	if (node)
		return (ft_strchr(node->content, '=') + 1);
	return (NULL);
}
