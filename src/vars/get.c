/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 02:38:37 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/16 00:47:06 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_var(const char *arg, const char *env)
{
	uint32_t	i;

	if (!arg || !env)
		return (false);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=' && !arg[i])
			return (true);
		if (env[i] != arg[i])
			return (false);
		i++;
	}
	return (false);
}

t_list	*ms_vars_get_node(t_list *list, const char *arg)
{
	if (!list || !arg)
		return (NULL);
	while (list)
	{
		if (check_var(arg, list->content))
			return (list);
		list = list->next;
	}
	return (NULL);
}

bool	ms_vars_parse(t_var *var, const char *str)
{
	size_t	varname_size;

	if (!var || !str || !ft_strchr(str, '='))
		return (false);
	ft_memset(var->name, 0, VARNAME_BUFFER);
	ft_memset(var->value, 0, VAR_BUFFER);
	varname_size = (ft_strchr(str, '=') - str) + 1;
	if (varname_size > VARNAME_BUFFER)
		varname_size = VARNAME_BUFFER;
	ft_strlcpy(var->name, str, varname_size);
	ft_strlcpy(var->value, ft_strchr(str, '=') + 1, VAR_BUFFER);
	if (!var->name[0] || !var->value[0])
		return (false);
	return (true);
}

char	*ms_vars_get_var(t_list *list, const char *arg)
{
	t_list	*node;

	node = ms_vars_get_node(list, arg);
	if (node)
		return (ft_strchr(node->content, '=') + 1);
	return (NULL);
}
