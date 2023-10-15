/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:39:26 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/14 22:41:18 by niceguy          ###   ########.fr       */
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