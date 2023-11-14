/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:25:44 by aroussea          #+#    #+#             */
/*   Updated: 2023/11/14 17:51:14 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

static char	*cut_quotes(char *str, char **tmp)
{
	size_t	len;
	char	*dst_tmp;
	char	*rep;

	len = ft_strlen(str) - ft_strlen(*tmp);
	(*tmp)++;
	dst_tmp = ft_calloc(len + 1, sizeof(char));
	if (!dst_tmp)
	{
		ft_putstr_fd("Erreur, malloc!\n", 2);
		return (NULL);
	}
	ft_strlcpy(dst_tmp, str, len + 1);
	rep = ft_strjoin(dst_tmp, *tmp);
	free(dst_tmp);
	return (rep);
}

static char	*quote_operation(int *dquotes, int *quotes, char *str, char **tmp)
{
	if (**tmp == '\'' && *dquotes == 0)
	{
		if (*quotes == 0)
			(*quotes)++;
		else 
			(*quotes)--;
		str = cut_quotes(str, tmp);
	}
	if (**tmp == '"' && *quotes == 0)
	{
		if (*dquotes == 0)
			(*dquotes)++;
		else 
			(*dquotes)--;
		str = cut_quotes(str, tmp);
	}
	return (str);
}

char	*quotes_handler(char *str)
{
	char	*tmp;
	int		dquotes;
	int		quotes;

	dquotes = 0;
	quotes = 0;
	str = check_expand(str);
	tmp = str;
	if (!check_if_quotes(tmp))
		return (str);
	while (*tmp)
	{
		str = quote_operation(&dquotes, &quotes, str, &tmp);
		if ((quotes == 0 && dquotes == 0) && (*tmp == '\'' || *tmp == '"'))
			continue ;
		if ((dquotes == 1 && *tmp == '"') || (quotes == 1 && *tmp == '\''))
			continue ;
		if (*tmp == 0)
			return (str);
		tmp++;
	}
	return (str);
}
