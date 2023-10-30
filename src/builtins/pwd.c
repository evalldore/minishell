/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:17:59 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/30 18:46:25 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_pwd(void)
{
	char	*path;

	path = ms_vars_get_var(ms_get()->env_list, "PWD");
	if (path)
		printf("%s\n", path);
}
