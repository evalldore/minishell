/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 02:38:37 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/02 15:17:34 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_var(const char *arg, const char *env)
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

t_list	*ms_env_get_node(const char *arg)
{
	t_list		*env_list;

	if (!arg)
		return (NULL);
	env_list = ms_env_get();
	while (env_list)
	{
		if (is_var(arg, env_list->content))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*ms_env_get_var(const char *arg)
{
	t_list	*node;

	node = ms_env_get_node(arg);
	if (node)
		return (ft_strchr(node->content, '=') + 1);
	return (NULL);
}
