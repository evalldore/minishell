/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:30:49 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/14 14:41:56 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_separator(char *str)
{
	int	dquotes;
	int	quotes;

	dquotes = 0;
	quotes = 0;
	while (*str && ft_strchr(OPERATORS, *str))
		str++;
	while (*str)
	{
		if ((ft_strchr(WHITESPACES, *str) || ft_strchr(OPERATORS, *str)) 
			&& quotes == 0 && dquotes == 0)
			return (str);
		quote_counter(&dquotes, &quotes, *str);
		str++;
	}
	return (NULL);
}

static int	token_type(char *str)
{
	if (!str || !*str)
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
	}
	sub = quotes_handler(separation(str));
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
			ms_terminate(1, "Minishell: Couldnt allocate memory for token!\n");
		node = ft_lstnew(token);
		if (!node)
			ms_terminate(1, "Minishell: Couldnt allocate memory for token!\n");
		ft_lstadd_back(&list, node);
		input = find_separator(input);
	}
	ms->tokens = list;
}
