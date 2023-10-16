/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:03:42 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/15 17:13:04 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_var(const char *arg, const char *var)
{
	size_t	len;
	char	*buff;
	t_list	*node;

	if (!arg || var)
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
	ft_lstadd_back(&ms_get()->env_list, node);
}

void	ms_env_set_var(const char *arg, const char *var)
{
	t_list	*node;
	char	*str;
	char	*buff;
	size_t	len;

	if (!arg || !var)
		return ;
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
	else
		add_var(arg, var);
}

void	ms_env_del_var(const char *arg)
{
	t_list	*node;
	t_list	*env_list;

	if (!arg)
		return ;
	node = ms_env_get_node(arg);
	env_list = ms_get()->env_list;
	if (!node)
		return ;
	while (env_list->next)
	{
		if (env_list->next && env_list->next == node)
		{
			env_list->next = node->next;
			ft_lstdelone(node, free);
			return ;
		}
		env_list = env_list->next;
	}
}
