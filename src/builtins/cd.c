/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:10:46 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/15 17:47:36 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_cd(size_t argc, char	**args)
{
	t_minishell	*ms;
	char		pwd[PATH_BUFFER];
	char		*path;
	char		*curr;

	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	ms = ms_get();
	path = args[1];
	if (!path || (path[0] == '~' && !path[1]))
		path = ms_vars_get_var(ms->env_list, "HOME");
	if (chdir(path) != 0)
		return (perror("cd"));
	if (ms_vars_get_node(ms->env_list, "PWD"))
	{
		curr = ms_vars_get_var(ms->env_list, "PWD");
		ms_vars_set(&ms->env_list, "OLDPWD", curr);
	}
	ms_vars_set(&ms->env_list, "PWD", getcwd(pwd, PATH_BUFFER));
}
