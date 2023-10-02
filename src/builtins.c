/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:49:52 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/02 15:33:26 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_exec(const char *cmd, const char **args)
{
	t_minishell	*ms;

	ms = ms_get();
	if (ft_strncmp(cmd, "echo") == 0)
		return (ms_builtin_echo(args))
}