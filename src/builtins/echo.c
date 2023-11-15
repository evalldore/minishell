/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:20:17 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/15 16:10:37 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_echo(char **args)
{
	bool	nl;

	nl = true;
	if (*args)
	{
		if (*args[0] && ft_strncmp(*args, "-n", ft_strlen(*args)) == 0)
		{
			nl = false;
			args++;
		}
		while (*args)
		{
			ft_putstr_fd(*args++, STDOUT_FILENO);
			if (*args)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
