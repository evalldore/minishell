/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:25:44 by aroussea          #+#    #+#             */
/*   Updated: 2023/10/11 16:00:35 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_quotes(char *str)
{
	char	*c;

	c = NULL;
	while (*str != find_separator(str))
	{
		if (*str == '"' || *str == '\'')
		{
			if (c == *str)
				
			c = *str;
		}
		str++;
	}
}