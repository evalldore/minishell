/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:20:11 by aroussea          #+#    #+#             */
/*   Updated: 2023/11/16 15:49:47 by aroussea         ###   ########.fr       */
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

static char	*sep_operateur(char *str)
{
	int		len;
	char	*dst;

	if (((*str == *(str + 1)) && (*str == '|')) 
		|| ((*str == '>' || *str == '<') 
			&& (*str == *(str + 1)) && (*str == *(str + 2))))
	{
		ft_putstr_fd("Minishell: Operateur Invalide Syntax!\n", 2);
		return (NULL);
	}
	len = 1;
	if ((*str == *(str + 1)) && (*str == '>' || *str == '<'))
		len++;
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
	{
		ft_putstr_fd("Erreur, malloc!\n", 2);
		return (NULL);
	}
	ft_strlcpy(dst, str, len + 1);
	return (dst);
}

static char	*retour_separation(size_t len, char *str)
{
	char	*dst;

	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
	{
		ft_putstr_fd("Erreur, malloc!\n", 2);
		return (NULL);
	}
	ft_strlcpy(dst, str, len + 1);
	return (dst);
}

char	*separation(char *str)
{
	char	*nsep;

	nsep = find_separator(str, 0);
	if (!(nsep - str))
		return (sep_operateur(str));
	if (!nsep)
		return (retour_separation(ft_strlen(str), str));
	return (retour_separation(nsep - str, str));
}
