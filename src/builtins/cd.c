/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:10:46 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/03 00:56:28 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_cd(char	*path)
{
	t_list	*node;

	if (access(path, F_OK) != 0)
		return ;
	node = ms_env_get_node("PWD");
	if (node)
	{
		ms_env_set_var("OLDPWD", ms_env_get_var("PWD"));
		ms_env_set_var("PWD", path);
	}
	else
		printf("cd: no working direction");
}
