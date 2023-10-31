/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:03:42 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/30 22:04:31 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_var(t_list **list, const char *arg, const char *var)
{
	size_t	len;
	char	*buff;
	t_list	*node;

	if (!arg || !var)
		return ;
	len = ft_strlen(arg) + ft_strlen(var) + 1;
	buff = ft_calloc(len + 1, sizeof(char));
	if (!buff)
		return ;
	ft_strlcpy(buff, arg, ft_strlen(arg) + 1);
	buff[ft_strlen(arg)] = '=';
	ft_strlcat(buff, var, len + 1);
	node = ft_lstnew(buff);
	if (!node)
	{
		free(buff);
		return ;
	}
	ft_lstadd_back(list, node);
}

void	ms_vars_set(t_list **list, const char *arg, const char *var)
{
	t_list	*node;
	char	*str;
	char	*buff;
	size_t	len;

	if (!arg || !var)
		return ;
	node = ms_vars_get_node(*list, arg);
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
	else
		add_var(list, arg, var);
}

void	ms_vars_del(t_list *list, const char *arg)
{
	t_list	*node;

	if (!arg)
		return ;
	node = ms_vars_get_node(list, arg);
	if (!node)
		return ;
	while (list->next)
	{
		if (list->next && list->next == node)
		{
			list->next = node->next;
			ft_lstdelone(node, free);
			return ;
		}
		list = list->next;
	}
}
