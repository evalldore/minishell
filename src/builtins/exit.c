/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:28:54 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/26 16:20:48 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_exit(size_t argc, char **args)
{
	t_minishell	*ms;

	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
	ms = ms_get();
	ms->running = false;
	ms->status = ft_atoi(args[1]);
}
