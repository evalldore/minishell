/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:03:17 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/15 18:15:43 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_unset(char **arg)
{
	if (!arg)
		return ;
	while (*arg)
	{
		ms_vars_del(ms_get()->env_list, *arg);
		arg++;
	}
}
