/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:28:54 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/14 23:24:31 by niceguy          ###   ########.fr       */
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
	ms->status = (uint8_t)ft_atoi(args[1]);
}
