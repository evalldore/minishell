/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:30:49 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/11 15:34:41 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_separator(char *str)
{
	bool	is_op;

	if (!str)
		return (NULL);
	is_op = ft_strchr(OPERATORS, *str) != NULL;
	while (*str)
	{
		if (is_op && !ft_strchr(OPERATORS, *str))
			return (str);
		if (!is_op && (ft_strrchr(WHITESPACES, *str) || ft_strchr(OPERATORS, *str)))
			return (str);
		str++;
	}
	return (str);
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

static t_token	*create_token(char *str)
{
	t_token	*token;
	char	*sub;
	size_t	len;

	if (!str)
		return (NULL);
	sub = parse_quotes(str);
	if (!sub)
	{
		len = find_separator(str) - str;
		sub = ft_calloc(len + 1, sizeof(char));
		if (!sub)
			return (NULL);
		token = ft_calloc(1, sizeof(t_token));
		if (!token)
		{
			free(sub);
			return (NULL);
		}
		ft_strlcpy(sub, str, len + 1);
	}
	token->type = token_type(sub);
	token->str = sub;
	return (token);
}

void	ms_tokens_init(char	*input)
{
	t_minishell	*ms;
	t_list		*list;
	t_list		*node;
	t_token		*token;

	list = NULL;
	ms = ms_get();
	while (*input)
	{
		while (*input && ft_strchr(WHITESPACES, *input))
			input++;
		if (!*input)
			break ;
		token = create_token(input);
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
