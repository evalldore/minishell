/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:00:19 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/12 22:13:22 by niceguy          ###   ########.fr       */
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

void	ms_env_clear(void)
{
	t_list	*env_list;

	env_list = ms_get()->env_list;
	if (env_list)
		ft_lstclear(&env_list, free);
}

char	**ms_env_path(void)
{
	char		**arr;
	char		*temp;
	size_t		index;
	char		*paths;

	paths = ms_env_get_var("PATH");
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
