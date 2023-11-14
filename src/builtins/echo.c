/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:20:17 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/14 17:00:34 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_param(char	*str)
{
	size_t		i;
	const char	*p;

	if (!str)
		return (false);
	i = 0;
	p = "-n";
	while (p[i])
	{
		if (p[i] != str[i])
			return (false);
		i++;
	}
	return (true);
}

void	ms_builtin_echo(char **args)
{
	bool	nl;

	nl = true;
	if (is_param(*args))
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
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
