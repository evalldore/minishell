/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:30:49 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/16 15:39:10 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_separator(char *str, int i)
{
	int	quotes[2];
	int	x;

	quotes[0] = 0;
	quotes[1] = 0;
	x = 0;
	if (i != 0 && (quotes[0] == 0 && quotes[1] == 0))
	{
		while (*str && ft_strchr(OPERATORS, *str))
		{
			str++;
			x = 1;
		}
		if (x == 1)
			return (str);
	}
	while (*str)
	{
		if ((ft_strchr(WHITESPACES, *str) || ft_strchr(OPERATORS, *str)) 
			&& quotes[0] == 0 && quotes[1] == 0)
			return (str);
		quote_counter(&quotes[1], &quotes[0], *str);
		str++;
	}
	return (NULL);
}

static int	token_type(char *str)
{
	if (!str)
		return (TOK_NONE);
	if (*str == '>')
		return (TOK_REDIR);
	if (*str == '<')
		return (TOK_REDIR);
	if (*str == '|')
		return (TOK_PIPE);
	return (TOK_TEXT);
}

static t_token	*create_token(char *str, int *check)
{
	t_token	*token;
	char	*sub;

	if (!str)
		return (NULL);
	if (check_unclosed_quote(str))
	{
		*check = 1;
		ft_putstr_fd("Minishell : Unclosed quotes!\n", 2);
		return (NULL);
	}
	sub = separation(str);
	if (!sub)
	{
		*check = 1;
		return (NULL);
	}
	sub = quotes_handler(sub);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		free(sub);
		return (NULL);
	}
	token->type = token_type(sub);
	token->str = sub;
	return (token);
}

void	ms_tokens_init(char	*input, int *check)
{
	t_minishell	*ms;
	t_list		*list;
	t_list		*node;
	t_token		*token;

	list = NULL;
	ms = ms_get();
	while (input && *input)
	{
		while (*input && ft_strchr(WHITESPACES, *input))
			input++;
		if (!*input)
			break ;
		token = create_token(input, check);
		if (*check != 0)
			break ;
		if (!token)
			ms_free_token_init(input, token, &list);
		node = ft_lstnew(token);
		if (!node)
			ms_free_token_init(input, token, &list);
		ft_lstadd_back(&list, node);
		input = find_separator(input, 1);
	}
	ms->tokens = list;
}
