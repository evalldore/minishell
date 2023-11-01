/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:25:44 by aroussea          #+#    #+#             */
/*   Updated: 2023/11/01 16:13:19 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_counter(int *dquotes, int *quotes, char c)
{
	if (c == '\'' && *quotes == 0 && *dquotes == 0)
		(*quotes)++;
	else if (c == '\'' && *quotes == 1 && *dquotes == 0)
		(*quotes)--;
	if (c == '"' && *dquotes == 0 && *quotes == 0)
		(*dquotes)++;
	else if (c == '"' && *dquotes == 1 && *quotes == 0)
		(*dquotes)--;
	return ;
}

int	check_unclosed_quote(char *str)
{
	int	dquotes;
	int quotes;

	dquotes = 0;
	quotes = 0;
	while (*str != '\0')
	{
		quote_counter(&dquotes, &quotes, *str);
		str++;
	}
	if (dquotes != 0 || quotes != 0)
		return (1);
	return (0);
}

char	*separation(char *str)
{
	char	*nsep;
	size_t	len;
	char	*dst;

	nsep = find_separator(str);
	if (!nsep)
	{
		dst = ft_calloc(ft_strlen(str) + 1, sizeof(char));
		ft_strlcpy(dst, str, ft_strlen(str) + 1);
		return (dst);
	}
	len = nsep - str;
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
	{
		printf("Erreur, malloc!\n");
		return (NULL);
	}
	ft_strlcpy(dst, str, len + 1);
	return (dst);
}

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

char	*cut_quotes(char *str)
{
	char	*tmp;
	char	*dst_tmp;
	char	*rep;
	int		dquotes;
	int		quotes;
	size_t	len;

	dquotes = 0;
	quotes = 0;
	str = check_expand(str);
	tmp = str;
	if (!check_if_quotes(tmp))
		return (str);
	while (*tmp)
	{
		if (*tmp == '\'' && dquotes == 0)
		{
			if (quotes == 0)
				quotes++;
			else 
				quotes--;
			len = ft_strlen(str) - ft_strlen(tmp);
			tmp++;
			dst_tmp = ft_calloc(len + 1, sizeof(char));
			if (!dst_tmp)
			{
				printf("Erreur, malloc!\n");
				return (NULL);
			}
			ft_strlcpy(dst_tmp, str, len + 1);
			rep = ft_strjoin(dst_tmp, tmp);
			str = rep;
			free(dst_tmp);
		}
		if (*tmp == '"' && quotes == 0)
		{
			if (dquotes == 0)
				dquotes++;
			else 
				dquotes--;
			len = ft_strlen(str) - ft_strlen(tmp);
			tmp++;
			dst_tmp = ft_calloc(len + 1, sizeof(char));
			if (!dst_tmp)
			{
				printf("Erreur, malloc!\n");
				return (NULL);
			}
			ft_strlcpy(dst_tmp, str, len + 1);
			rep = ft_strjoin(dst_tmp, tmp);
			str = rep;
			free(dst_tmp);
		}
		if ((quotes == 0 && dquotes == 0) && (*tmp == '\'' || *tmp == '"'))
			continue ;
		if ((dquotes == 1 && *tmp == '"') || (quotes == 1 && *tmp == '\''))
			continue ;
		tmp++;
	}
	return (rep);
}
