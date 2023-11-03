/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:30 by aroussea          #+#    #+#             */
/*   Updated: 2023/11/02 21:46:51 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*var_name(char *str)
{
	char	*dst;
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	while (*str && (*str != '"' && *str != '\'' ) && !ft_strchr(WHITESPACES, *str))
	{
		i++;
		str++;
	}
	tmp++;
	dst = ft_calloc(i, sizeof(char));
	ft_strlcpy(dst, tmp, i);
	return (dst);
}

char	*expand(char *str)
{
	char	*arg;
	char	*tmp;

	tmp = var_name(str);
	arg = ms_vars_get_var(ms_get()->env_list, tmp);
	if (!arg)
		arg = ms_vars_get_var(ms_get()->var_list, tmp);
	free(tmp);
	if (!arg)
		return (NULL);
	return (arg);
}

static char	*combine(char *first, char *second)
{
	char	*dst;

	second++;
	while (*second && (*second != '"' && *second != '\'' ) && !ft_strchr(WHITESPACES, *second))
		second++;
	dst = ft_strjoin(first, second);
	return (dst);
}

char	*check_expand(char *str)
{
	char	*tmp;
	char	*dst;
	size_t	len;
	int		quotes;
	int		dquotes;

	tmp = str;
	quotes = 0;
	dquotes = 0;
	while (*tmp)
	{
		quote_counter(&dquotes, &quotes, *tmp);
		if (*tmp == '$' && quotes == 0)
		{
			len = ft_strlen(str) - ft_strlen(tmp);
			dst = ft_calloc(len + 1, sizeof(char));
			if (!dst)
			{
				printf("Erreur, malloc!\n");
				return (NULL);
			}
			ft_strlcpy(dst, str, len + 1);
			tmp = expand(tmp);
			if (!tmp)
				str = combine(dst, str);
			else
				str = combine(ft_strjoin(dst, tmp), str);
			tmp = str;
		}
		tmp++;
	}
	return (str);
}
