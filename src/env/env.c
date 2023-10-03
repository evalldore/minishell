/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:00:19 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/03 02:01:55 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env_init(char **env)
{
	char	*copy;
	t_list	*new;

	while (*env)
	{
		copy = ft_strdup(*env);
		if (!copy)
			return ;
		new = ft_lstnew(copy);
		if (!new)
			return ;
		ft_lstadd_back(&ms_get()->env_list, new);
		env++;
	}
}

void	ms_env_clear(void)
{
	t_list	*env_list;

	env_list = ms_get()->env_list;
	if (env_list)
		ft_lstclear(&env_list, free);
}
