/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:03:42 by niceguy           #+#    #+#             */
/*   Updated: 2023/09/27 04:57:57 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env_set_var(const char *arg, const char *var)
{
	t_list	*node;
	char	*str;
	char	*buff;
	size_t	len;

	node = ms_env_get_node(arg);
	if (node)
	{
		str = node->content;
		len = ft_strlen(arg) + ft_strlen(var) + 1;
		buff = ft_calloc(len + 1, sizeof(char));
		if (!buff)
			return ;
		ft_strlcpy(buff, str, (ft_strchr(str, '=') - str) + 2);
		ft_strlcat(buff, var, len + 1);
		node->content = buff;
		free(str);
	}
}
