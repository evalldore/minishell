/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:55:10 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/08 23:49:19 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_terminate(int status, char	*msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	ms_env_clear();
	exit(status);
}

void	ms_array_free(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

size_t	ms_array_count(void **array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
