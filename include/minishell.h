/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:07 by evallee-          #+#    #+#             */
/*   Updated: 2023/11/15 18:16:19 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <stdbool.h>
# include <signal.h>
# define COLOR_RED "\x1b[31m"
# define COLOR_GREEN "\x1b[32m"
# define COLOR_YELLOW "\x1b[33m"
# define COLOR_BLUE "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN "\x1b[36m"
# define COLOR_RESET "\x1b[0m"
# define PROMPT	"\x1b[32mMinishit\x1b[0m > "
# define MAX_ARGS 1024
# define MAX_NODE 1024
# define PATH_BUFFER 256
# define VARNAME_BUFFER 256
# define VAR_BUFFER 512
# define HEREDOC_BUFFER 1024
# define WHITESPACES " \t\r\n\v"
# define OPERATORS "<|>"
# ifndef DEBUG
#  define DEBUG 0
# endif

enum	e_cmd
{
	CMD_EXEC,
	CMD_REDIR,
	CDM_PIPE,
	CMD_HEREDOC,
	MAX_CMD
};

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_cmd_heredoc
{
	int		type;
	char	buffer[HEREDOC_BUFFER];
	t_cmd	*cmd;
	char	*eof;
}	t_cmd_heredoc;

typedef struct s_cmd_exec
{
	int			type;
	char		*argv[MAX_ARGS];
	uint32_t	argc;
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

enum	e_mode
{
	MODE_DEFAULT,
	MODE_MAIN,
	MODE_HEREDOC,
	MODE_IGN
};

enum	e_token
{
	TOK_NONE,
	TOK_TEXT,
	TOK_PIPE,
	TOK_REDIR,
	MAX_TOK
};

enum	e_builtin
{
	BI_NONE,
	BI_CAT,
	BI_PWD,
	BI_CD,
	BI_ENV,
	BI_EXIT,
	BI_EXPORT,
	BI_ECHO,
	BI_UNSET,
	MAX_BI
};

typedef struct s_token
{
	char			*str;
	int				type;
}	t_token;

typedef struct s_var
{
	char	name[VARNAME_BUFFER];
	char	value[VAR_BUFFER];
}	t_var;

typedef struct s_minishell
{
	bool		running;
	uint8_t		status;
	t_list		*tokens;
	t_list		*env_list;
	t_list		*var_list;
	t_cmd		*cmd;
}	t_minishell;

t_cmd		*ms_node_exec(void);
t_cmd		*ms_node_pipe(t_cmd *left, t_cmd *right);
t_cmd		*ms_node_redir(t_cmd *next, char *file, int fd, int mode);
t_cmd		*ms_node_heredoc(t_cmd *next, char *eof);

void		ms_heredoc_write(char *buffer, char *eof);

t_minishell	*ms_get(void);
bool		ms_init(char **env);
char		*ms_input(void);
void		ms_status(int status);

t_cmd		*ms_cmd_parse(t_list *tokens);
void		ms_cmd_run(t_cmd *cmd);
void		ms_cmd_free(t_cmd **cmd);
void		ms_cmd_pipe(t_cmd *left, t_cmd *right);
void		ms_cmd_heredoc(char *buffer, t_cmd *cmd);

bool		ms_builtin_exec(size_t argc, char **args);
void		ms_builtin_env(void);
void		ms_builtin_echo(char **args);
void		ms_builtin_exit(size_t argc, char **args);
void		ms_builtin_cd(size_t argc, char **args);
void		ms_builtin_export(const char *str);
void		ms_builtin_unset(char **arg);
void		ms_builtin_pwd(void);
bool		ms_builtin(t_list *tokens);

void		ms_tokens_init(char	*input, int *check);
bool		ms_tokens_peek(t_list **list, int type);
t_token		*ms_tokens_get(t_list **list);
void		ms_tokens_del(void	*ptr);

char		*find_separator(char *str);
char		*separation(char *str);
char		*quotes_handler(char *str);
int			check_unclosed_quote(char *str);
void		quote_counter(int *dquotes, int *quotes, char c);

char		*expand(char *str);
char		*check_expand(char *str);

bool		ms_env_init(char **env);
char		**ms_env_path(void);
char		**ms_env_array(void);

char		*ms_vars_get_var(t_list *list, const char *arg);
t_list		*ms_vars_get_node(t_list *list, const char *arg);
void		ms_vars_set(t_list **list, const char *arg, const char *var);
void		ms_vars_del(t_list *list, const char *arg);
bool		ms_vars_parse(t_var *var, const char *str);

void		ms_array_free(void **array);
size_t		ms_array_count(void **array);
char		*ms_path_find(char *cmd);

void		ms_terminate(int status, char *msg);

void		ms_debug_child(int pid, int status);

void		*ms_alloc(size_t size);
void		ms_alloc_reset(void);

void		ms_signal_set(int mode);

#endif
