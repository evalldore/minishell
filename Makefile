NAME			:= minishell
CFLAGS			:= -Wall -Wextra -Werror -g
SRCS			:= main.c utils.c constructors.c debug.c pipe.c allocator.c minishell.c
TOKENSRCS		:= token.c list.c
ENVSRCS			:= get_env.c env.c set_env.c
BUILTSRCS		:= env.c echo.c pwd.c cd.c unset.c export.c exit.c builtins.c
CMDSRCS			:= commands.c parsing.c 
INCDIR			:= include/
BINDIR			:= bin/
SRCDIR			:= src/
TOKENDIR		:= token/
BUILTDIR		:= builtins/
CMDSDIR			:= commands/
ENVDIR			:= env/
LIBFT			:= ./lib/libft
RM				:= rm -f
HEADERS			:= -I ./include -I $(LIBFT)/include
CC				:= gcc
LIBS			:= $(LIBFT)/libft.a
SRCS			+= $(addprefix $(TOKENDIR), $(TOKENSRCS))
SRCS			+= $(addprefix $(ENVDIR), $(ENVSRCS))
SRCS			+= $(addprefix $(BUILTDIR), $(BUILTSRCS))
SRCS			+= $(addprefix $(CMDSDIR), $(CMDSRCS))
OBJS			:= $(addprefix $(BINDIR), $(SRCS:.c=.o))

all : libraries $(NAME)

leaks:
	valgrind --track-fds=yes --show-leak-kinds=all --show-reachable=no --trace-children=yes --leak-check=full ./minishell

libraries :
	@$(MAKE) -C $(LIBFT)

$(BINDIR)%.o : $(SRCDIR)%.c
	@$(CC) -c $(CFLAGS) -o $@ $^ $(HEADERS)

$(NAME) : $(BINDIR) $(OBJS)
	@echo $(NAME): Compiling!
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(HEADERS) -lreadline

$(BINDIR) :
	@mkdir $(BINDIR)
	@mkdir $(BINDIR)$(TOKENDIR)
	@mkdir $(BINDIR)$(ENVDIR)
	@mkdir $(BINDIR)$(BUILTDIR)
	@mkdir $(BINDIR)$(CMDSDIR)

clean:
	@$(MAKE) -C $(LIBFT) fclean
	@echo $(NAME): Deleting binaries.
	@rm -r $(BINDIR)

fclean: clean
	@echo $(NAME): Deleting program.
	@rm -f $(NAME)

re : fclean all