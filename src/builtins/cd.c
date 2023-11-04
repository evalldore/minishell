/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:10:46 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/03 22:46:23 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_cd(size_t argc, char	**args)
{
	t_list	*node;
	char	pwd[PATH_BUFFER];
	char	*path;

	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	path = args[1];
	if (!path || (path[0] == '~' && !path[1]))
		path = ms_vars_get_var(ms_get()->env_list, "HOME");
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	node = ms_vars_get_node(ms_get()->env_list, "PWD");
	if (node)
		ms_vars_set(&(ms_get()->env_list), "OLDPWD", (char *)node->content);
	ms_vars_set(&(ms_get()->env_list), "PWD", getcwd(pwd, PATH_BUFFER));
}
