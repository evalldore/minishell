/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:55:10 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/01 23:24:04 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_array_free(void **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

size_t	ms_array_count(void **array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*ms_path_find(char *cmd)
{
	char	*cmd_path;
	char	**paths;
	size_t	path_i;

	if (!cmd)
		return (NULL);
	paths = ms_env_path();
	if (!paths)
		return (NULL);
	path_i = 0;
	while (paths[path_i])
	{
		cmd_path = ft_strjoin(paths[path_i++], cmd);
		if (!cmd_path)
			break ;
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ms_array_free((void **)paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ms_array_free((void **)paths);
	return (NULL);
}
