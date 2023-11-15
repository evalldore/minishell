/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:58:57 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/15 17:41:31 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	transfer_top(t_list *node)
{
	ms_get()->var_list = node->next;
	node->next = NULL;
	ft_lstadd_back(&(ms_get()->env_list), node);
}

static bool	set(const char *str)
{
	t_var		var;
	t_minishell	*ms;

	if (!str)
		return (false);
	ms = ms_get();
	if (ms_vars_parse(&var, str))
	{
		ms_vars_set(&ms->env_list, var.name, var.value);
		return (true);
	}
	return (false);
}

static void	print_env(void)
{
	t_list	*env_list;

	env_list = ms_get()->env_list;
	while (env_list)
	{
		printf("declare -x %s\n", (char *)env_list->content);
		env_list = env_list->next;
	}
}

void	ms_builtin_export(const char *str)
{
	t_list			*node;
	t_list			*list;

	if (!str)
		print_env();
	if (set(str))
		return ;
	list = ms_get()->var_list;
	node = ms_vars_get_node(list, str);
	if (!list || !node)
		return ;
	if (list == node)
		return (transfer_top(node));
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
