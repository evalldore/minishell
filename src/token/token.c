/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:30:49 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/03 16:48:24 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_prev(t_token *token, t_token *last)
{
	while (token->next->prev)
	{
		token = token->next;
	}
	last->prev = token;
}

static t_token	*last_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static void	add_list(t_token **token, t_token *new)
{
	if (!new)
		return ;
	if (!(*token))
	{
		*token = new;
		return ;
	}
	last_token(*token)->next = new;
}

static t_token	*creat_token(char *string)
{
	t_token	*token;
	
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return NULL;
	token->str = string;
	return (token);
}

void	ms_token_init(char *input)
{
	int			i;
	char		**strings;
	t_minishell	*ms;
	t_token		*token;
	
	token = NULL;
	ms = ms_get();
	strings = parsing(input);
	i = 0;
	while(strings[i])
	{
		add_list(&token, creat_token(strings[i]));
		if (i != 0)
			add_prev(token, last_token(token));
		i++;
	}
	ms->tokens = token;
}
