/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:20:17 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/15 16:03:16 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_echo(char **args)
{
	bool	nl;
	char	*param;

	nl = true;
	param = *args;
	if (!param)
		return ;
	if (*param && ft_strncmp(param, "-n", ft_strlen(param)) == 0)
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
