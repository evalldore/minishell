/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:07 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/03 02:01:01 by niceguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <stdbool.h>
# include <stdio.h>
# include <signal.h>
# define COLOR_RED		"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_YELLOW	"\x1b[33m"
# define COLOR_BLUE		"\x1b[34m"
# define COLOR_MAGENTA	"\x1b[35m"
# define COLOR_CYAN		"\x1b[36m"
# define COLOR_RESET	"\x1b[0m"
# define PROMPT			"\x1b[32mminishit > \x1b[0m"

enum	e_token
{
	TOK_NONE,
	TOK_TRUNC,
	TOK_APPEND,
	TOK_INPUT,
	TOK_PIPE,
	TOK_END,
	TOK_CMD,
	TOK_ARG,
	MAX_TOK
};

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_minishell
{
	bool		running;
	int			status;
	t_token		*tokens;
	t_list		*env_list;
}	t_minishell;

t_minishell	*ms_get(void);

void		ms_builtin_env(void);
void		ms_builtin_echo(bool nl, char **msg);
void		ms_builtin_exit(int status);
void		ms_builtin_cd(char *path);
void		ms_builtin_export(const char *name, const char *var);
void		ms_builtin_unset(const char *arg);
void		ms_builtin_pwd(void);

void		ms_token_init(void);

void		ms_env_init(char **env);
void		ms_env_clear(void);
t_list		*ms_env_get_node(const char *arg);
char		*ms_env_get_var(const char *arg);
void		ms_env_set_var(const char *arg, const char *var);
void		ms_env_del_var(const char *arg);

#endif