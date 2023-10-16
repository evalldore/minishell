/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 02:38:37 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/16 14:08:09 by evallee-         ###   ########.fr       */
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
	env_list = ms_get()->env_list;
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

char	**ms_env_array(void)
{
	t_minishell		*ms;
	char			**array;
	size_t			i;
	t_list			*env_list;

	ms = ms_get();
	env_list = ms->env_list;
	array = malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	i = 0;
	if (!array)
		return (NULL);
	while (env_list)
	{
		array[i++] = (char *)env_list->content;
		env_list = env_list->next;
	}
	array[i] = NULL;
	return (array);
}
