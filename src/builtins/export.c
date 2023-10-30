/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:58:57 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/30 18:44:08 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_export(const char *name, const char *var)
{
	if (!name || !var)
		return ;
	ms_vars_set(ms_get()->env_list, name, var);
}
