/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:20:11 by aroussea          #+#    #+#             */
/*   Updated: 2023/11/15 14:04:34 by aroussea         ###   ########.fr       */
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
	int	quotes;

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
		if (!dst)
		{
			ft_putstr_fd("Erreur, malloc!\n", 2);
			return (NULL);
		}
		ft_strlcpy(dst, str, ft_strlen(str) + 1);
		return (dst);
	}
	len = nsep - str;
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
	{
		ft_putstr_fd("Erreur, malloc!\n", 2);
		return (NULL);
	}
	ft_strlcpy(dst, str, len + 1);
	return (dst);
}
