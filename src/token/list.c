/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:39:03 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/12 22:40:18 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ms_token_get(t_list **list)
{
	t_token		*token;

	if (!(*list))
		return (NULL);
	token = (*list)->content;
	*list = (*list)->next;
	return (token);
}

bool	ms_token_peek(t_list **list, int type)
{
	t_token		*token;

	if (!(*list))
		return (false);
	token = (*list)->content;
	return (token->type == type);
}
