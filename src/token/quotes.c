/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:25:44 by aroussea          #+#    #+#             */
/*   Updated: 2023/10/13 15:31:19 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_next_quote(char *str)
{
	char	c;

	c = *str;
	str++;
	while (*str && c != *str)
		str++;
	return (str);
}

char	*parse_quotes(char *str, int *check)
{
	char	*s;
	size_t	len;
	char	*dst;
	

	s = NULL;
	len = 0;
	while (str != find_separator(str, 0))
	{
		if (*str == '"' || *str == '\'')
		{
			s = str;
			str = find_next_quote(str);
			if (!*str)
			{
				printf("Minishell : unclosed quotes!\n");
				*check = 1;
			}
			else if (*str == *s)
			{
				s++;
				len = str - s;
				dst = ft_calloc(1, len + 1);
				ft_strlcpy(dst, s, len + 1);
				return (dst);
			}
		}
		str++;
	}
	return (NULL);
}
