/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:10:46 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/02 17:22:38 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_cd(char	*path)
{
	t_list	*node;

	node = ms_env_get_node("PWD");
	if (node)
	{
		free(node->content);
		node->content = (void *)path; //check is path if valid XD
	}
}
