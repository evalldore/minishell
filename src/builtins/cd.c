/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:10:46 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/28 17:43:48 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_cd(size_t argc, char	**args)
{
	t_list	*node;
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
	node = ms_env_get_node("PWD");
	if (node)
	{
		ms_env_set_var("OLDPWD", ms_env_get_var("PWD"));
		ms_env_set_var("PWD", getcwd(path, PATH_BUFFER));
		return ;
	}
}
