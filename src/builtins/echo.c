/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:20:17 by niceguy           #+#    #+#             */
/*   Updated: 2023/09/29 00:58:09 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_echo(bool nl, char **msg)
{
	while (*msg)
	{
		ft_putstr_fd(*msg, 1);
		msg++;
		if (*msg)
			ft_putchar_fd(' ', 1);
	}
	if (nl)
		ft_putchar_fd('\n', 1);
}
