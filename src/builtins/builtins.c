/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:49:52 by niceguy           #+#    #+#             */
/*   Updated: 2023/11/08 23:38:06 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_builtin(char *str)
{
	size_t		len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "exit", len) == 0)
		return (BI_EXIT);
	if (ft_strncmp(str, "cd", len) == 0)
		return (BI_CD);
	if (ft_strncmp(str, "echo", len) == 0)
		return (BI_ECHO);
	if (ft_strncmp(str, "env", len) == 0)
		return (BI_ENV);
	if (ft_strncmp(str, "export", len) == 0)
		return (BI_EXPORT);
	if (ft_strncmp(str, "pwd", len) == 0)
		return (BI_PWD);
	if (ft_strncmp(str, "unset", len) == 0)
		return (BI_UNSET);
	return (BI_NONE);
}

bool	ms_builtin_exec(size_t argc, char **args)
{
	int		bi;

	if (!args || !(*args))
		return (false);
	bi = get_builtin(args[0]);
	if (bi == BI_NONE)
		return (false);
	if (bi == BI_EXIT)
		ms_builtin_exit(argc, args);
	else if (bi == BI_CD)
		ms_builtin_cd(argc, args);
	else if (bi == BI_ECHO)
		ms_builtin_echo(&args[1]);
	else if (bi == BI_ENV)
		ms_builtin_env();
	else if (bi == BI_EXPORT)
		ms_builtin_export(args[1]);
	else if (bi == BI_PWD)
		ms_builtin_pwd();
	else if (bi == BI_UNSET)
		ms_builtin_unset(args[1]);
	return (true);
}

bool	ms_builtin(t_list *tokens)
{
	char		*argv[MAX_ARGS];
	size_t		argc;

	if (!tokens)
		return (false);
	ft_memset(&argv, 0, sizeof(argv));
	argc = 0;
	while (tokens && argc < MAX_ARGS)
	{
		if (ms_tokens_peek(&tokens, TOK_TEXT))
			argv[argc++] = ms_tokens_get(&tokens)->str;
		else
			return (false);
	}
	argv[argc] = NULL;
	return (ms_builtin_exec(argc, argv));
}
