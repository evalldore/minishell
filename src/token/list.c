/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:39:03 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/30 16:26:58 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ms_tokens_get(t_list **list)
{
	t_token		*token;

	if (!(*list))
		return (NULL);
	token = (*list)->content;
	*list = (*list)->next;
	return (token);
}

bool	ms_tokens_peek(t_list **list, int type)
{
	t_token		*token;

	if (!(*list))
		return (false);
	token = (*list)->content;
	return (token->type == type);
}
