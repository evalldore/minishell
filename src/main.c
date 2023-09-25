/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:51 by evallee-          #+#    #+#             */
/*   Updated: 2023/09/25 15:59:21 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	g_ms;

static void	init(void)
{
	g_ms.running = true;
	g_ms.name = "minishit > ";
}

int	main(int argc, char **argv)
{
	char	*input;

	(void)argc;
	(void)argv;
	init();
	while (g_ms.running)
	{
		input = readline(g_ms.name);
		ft_printf("%s\n", input);
	}
}
