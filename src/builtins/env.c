/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:09:57 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/03 01:13:47 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_env(void)
{
	t_list	*env_list;

	env_list = ms_env_get();
	while (env_list)
	{
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}
