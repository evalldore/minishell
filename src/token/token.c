/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:30:49 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/03 14:08:05 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*creat_token(char *string)
{
	t_token *token;
	
	token = ft_calloc(1, sizeof(token));
	if (!token)
		return NULL;
	token->str = string;
	return (token);
}

void	ms_token_init(char *input)
{
	int	i;
	char **strings;
	t_minishell	*ms;
	t_token	*token;
	
	ms = ms_get();
	strings = parsing(input);
	i = 0;
	while(strings[i])
	{
		if (i == 0)
			token = creat_token(strings[i]);
		else
		{
			
		}
		i++;
	}
}
