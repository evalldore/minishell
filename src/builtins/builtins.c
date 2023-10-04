/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:49:52 by niceguy           #+#    #+#             */
/*   Updated: 2023/10/03 20:32:37 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_builtin_exec(char **args)
{
	char		*bi;
	size_t		bi_len;

	if (!args)
		return (false);
	bi = args[0];
	bi_len = ft_strlen(bi);
	if (ft_strncmp(bi, "exit", bi_len) == 0)
		ms_builtin_exit(ft_atoi(args[1]));
	if (ft_strncmp(bi, "cd", bi_len) == 0)
		ms_builtin_cd(args[1]);
	if (ft_strncmp(bi, "echo", bi_len) == 0)
		ms_builtin_echo(&args[1]);
	if (ft_strncmp(bi, "env", bi_len) == 0)
		ms_builtin_env();
	if (ft_strncmp(bi, "export", bi_len) == 0)
		ms_builtin_export(args[1], args[2]); //export should set and add variables //export PISS=piss
	if (ft_strncmp(bi, "pwd", bi_len) == 0)
		ms_builtin_pwd();
	if (ft_strncmp(bi, "unset", bi_len) == 0)
		ms_builtin_unset(args[1]);
	return (false);
}
