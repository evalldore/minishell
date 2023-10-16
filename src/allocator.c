/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:41:55 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/15 17:13:25 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MB 1048576

static char	*get_alloc(void)
{
	static char	alloc[MB];

	return (&alloc[0]);
}

static char **get_pos()
{
	static char *pos;

	return (&pos);
}

void	ms_alloc_reset(void)
{
	static char **pos;

	pos = get_pos();
	*pos = get_alloc();
}

void	*ms_alloc(size_t size)
{
	char	**pos;
	char	*curr;
	char	*alloc;

	pos = get_pos();
	alloc = get_alloc();
	curr = *pos;
	if (&curr[size] > &alloc[MB])
		return (NULL);
	*pos = &curr[size];
	return (curr);
}
