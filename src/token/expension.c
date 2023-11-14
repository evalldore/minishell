/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:30 by aroussea          #+#    #+#             */
/*   Updated: 2023/11/14 17:43:14 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*var_name(char *str)
{
	char	*dst;
	char	*tmp;
	int		i;

	i = 1;
	str++;
	tmp = str;
	while (*str && (*str != '"' && *str != '\'' && *str != '$') 
		&& !ft_strchr(WHITESPACES, *str))
	{
		i++;
		str++;
	}
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

static char	*combine(char *first, char *s)
{
	char	*dst;
	char	*temp;

	temp = s;
	while (*s)
	{
		if (*s == '$')
		{
			s++;
			break ;
		}
		s++;
	}
	while (*s && (*s != '"' && *s != '\'' && *s != '$') 
		&& !ft_strchr(WHITESPACES, *s))
		s++;
	dst = ft_strjoin(first, s);
	free(temp);
	return (dst);
}

static	char	*expand_operation(char **str, char *tmp)
{
	size_t	len;
	char	*dst;
	char	*dst_join;

	len = ft_strlen(*str) - ft_strlen(tmp);
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
	{
		ft_putstr_fd("Erreur, malloc!\n", 2);
		return (NULL);
	}
	ft_strlcpy(dst, *str, len + 1);
	tmp = expand(tmp);
	if (!tmp)
		*str = combine(dst, *str);
	else
	{
		dst_join = ft_strjoin(dst, tmp);
		*str = combine(dst_join, *str);
		free(dst_join);
	}
	free(dst);
	return (*str);
}

char	*check_expand(char *str)
{
	char	*tmp;
	int		quotes;
	int		dquotes;

	tmp = str;
	quotes = 0;
	dquotes = 0;
	while (*tmp)
	{
		quote_counter(&dquotes, &quotes, *tmp);
		if (*tmp == '$' && quotes == 0)
			tmp = expand_operation(&str, tmp);
		if (*tmp == '$' && quotes == 0)
			continue ;
		if (*tmp == 0)
			return (str);
		tmp++;
	}
	return (str);
}
