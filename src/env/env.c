/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:00:19 by niceguy           #+#    #+#             */
/*   Updated: 2023/09/27 05:10:47 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ms_env_get()
{
	static t_list env_list;

	return (&env_list);
}

void	ms_env_init(char **env)
{
	t_list	*env_list;
	char	*copy;

	env_list = ms_env_get();
	while (*env)
	{
		copy = ft_strdup(*env);
		if (!copy)
			return ;
		ft_lstadd_back(&env_list, ft_lstnew(copy));
		env++;
	}
}

void	ms_env_clear()
{
	t_list	*env_list;

	env_list = ms_env_get();
	if (env_list)
		ft_lstclear(&env_list, free);
}
