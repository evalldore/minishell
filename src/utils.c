/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:55:10 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/16 15:37:44 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_token_init(char *input, t_token *token, t_list **list)
{
	free(input);
	if (token)
		ms_tokens_del(token);
	ft_lstclear(list, ms_tokens_del);
	ms_terminate(1, "Minishell: Couldnt allocate memory for token!\n");
}

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
