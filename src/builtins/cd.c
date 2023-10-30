/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:10:46 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/30 18:47:00 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_cd(size_t argc, char	**args)
{
	t_list	*node;
	t_list	*env_list;
	char	path[PATH_BUFFER];

	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return ;
	}
	env_list = ms_get()->env_list;
	node = ms_vars_get_node(ms_get()->env_list, "PWD");
	if (node)
	{
		ms_vars_set(env_list, "OLDPWD", ms_vars_get_var(env_list, "PWD"));
		ms_vars_set(env_list, "PWD", getcwd(path, PATH_BUFFER));
		return ;
	}
}
