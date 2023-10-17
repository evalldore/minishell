/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:39:26 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/16 14:08:18 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_tokens_del(void	*ptr)
{
	t_token		*token;

	token = ptr;
	if (token->str)
		free(token->str);
	free(ptr);
}
