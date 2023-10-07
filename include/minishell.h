/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niceguy <niceguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:07 by evallee-          #+#    #+#             */
/*   Updated: 2023/10/07 18:11:49 by niceguy          ###   ########.fr       */
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
# define COLOR_RED "\x1b[31m"
# define COLOR_GREEN "\x1b[32m"
# define COLOR_YELLOW "\x1b[33m"
# define COLOR_BLUE "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN "\x1b[36m"
# define COLOR_RESET "\x1b[0m"
# define PROMPT	COLOR_GREEN	"Minishit " COLOR_RESET "> "
# define MAX_ARGS 10
# define WHITESPACES " \t\r\n\v"
# define OPERATORS "<|>"

enum	e_cmd
{
	CMD_EXEC,
	CMD_REDIR,
	CDM_PIPE,
	CMD_LIST,
	CMD_BACK,
	MAX_CMD
};

typedef struct s_cmd
{
	int type;
}	t_cmd;

typedef struct s_cmd_exec
{
	int		type;
	char	*argv[MAX_ARGS];
	char	*eargv[MAX_ARGS];
}	t_cmd_exec;

typedef struct s_cmd_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		fd;
	int		mode;
}	t_cmd_redir;

typedef struct s_cmd_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_cmd_pipe;

enum	e_token
{
	TOK_NONE,
	TOK_TEXT,
	TOK_PIPE,
	TOK_REDIR,
	MAX_TOK
};

typedef struct s_token
{
	char			*str;
	int				type;
}	t_token;

typedef struct s_minishell
{
	bool		running;
	uint8_t		status;
	t_list		*tokens;
	t_list		*env_list;
	int			fd[2];
}	t_minishell;

t_cmd		*ms_node_exec(void);
t_cmd		*ms_node_pipe(t_cmd *left, t_cmd *right);
t_cmd		*ms_node_redir(t_cmd *next, char *file, int fd);

t_minishell	*ms_get(void);

t_cmd		*ms_cmd_parse(t_list *tokens);
void		ms_cmd_run(t_cmd *cmd);

bool		ms_builtin_exec(size_t argc, char **args);
void		ms_builtin_env(void);
void		ms_builtin_echo(char **args);
void		ms_builtin_exit(size_t argc, char **args);
void		ms_builtin_cd(size_t argc, char **args);
void		ms_builtin_export(const char *name, const char *var);
void		ms_builtin_unset(const char *arg);
void		ms_builtin_pwd(void);

t_list		*ms_tokens_init(char *input);

void		ms_env_init(char **env);
void		ms_env_clear(void);
t_list		*ms_env_get_node(const char *arg);
char		*ms_env_get_var(const char *arg);
void		ms_env_set_var(const char *arg, const char *var);
void		ms_env_del_var(const char *arg);

void		ms_array_free(void **array);
size_t		ms_array_count(void **array);

#endif