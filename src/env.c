/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:00:19 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/04 16:43:40 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_env_init(char **env)
{
	char	*copy;
	t_list	*new;

	if (!env)
		return (false);
	while (*env)
	{
		copy = ft_strdup(*env);
		if (!copy)
			return (false);
		new = ft_lstnew(copy);
		if (!new)
		{
			free(copy);
			return (false);
		}
		ft_lstadd_back(&ms_get()->env_list, new);
		env++;
	}
	return (true);
}

char	**ms_env_path(void)
{
	char		**arr;
	char		*temp;
	size_t		index;
	char		*paths;

	paths = ms_vars_get_var(ms_get()->env_list, "PATH");
	if (!paths)
		return (NULL);
	arr = ft_split(paths + 5, ':');
	index = 0;
	while (arr[index])
	{
		temp = arr[index];
		arr[index] = ft_strjoin(temp, "/");
		free(temp);
		index++;
	}
	return (arr);
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
