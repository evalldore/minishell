/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:00:19 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/02 15:20:02 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ms_env_get(void)
{
	static t_list	env_list;

	return (&env_list);
}

void	ms_env_init(char **env)
{
	t_list	*env_list;
	char	*copy;
	t_list	*new;

	env_list = ms_env_get();
	while (*env)
	{
		copy = ft_strdup(*env);
		if (!copy)
			return ;
		new = ft_lstnew(copy);
		if (!new)
			return ;
		ft_lstadd_back(&env_list, new);
		env++;
	}
}

void	ms_env_clear(void)
{
	t_list	*env_list;

	env_list = ms_env_get();
	if (env_list)
		ft_lstclear(&env_list, free);
}
