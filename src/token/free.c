/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:39:26 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/23 16:46:01 by aroussea         ###   ########.fr       */
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
