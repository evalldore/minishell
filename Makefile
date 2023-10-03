NAME			:= minishell
CFLAGS			:= -Wall -Wextra -Werror -g
SRCS			:= main.c utils.c builtins.c
TOKENSRCS		:= token.c parsing.c
ENVSRCS			:= get_env.c env.c set_env.c
BUILTSRCS		:= env.c echo.c pwd.c cd.c unset.c export.c exit.c
INCDIR			:= include/
BINDIR			:= bin/
SRCDIR			:= src/
TOKENDIR		:= token/
BUILTDIR		:= builtins/
ENVDIR			:= env/
LIBFT			:= ./lib/libft
RM				:= rm -f
HEADERS			:= -I ./include -I $(LIBFT)/include
CC				:= gcc
LIBS			:= $(LIBFT)/libft.a
SRCS			+= $(addprefix $(TOKENDIR), $(TOKENSRCS))
SRCS			+= $(addprefix $(ENVDIR), $(ENVSRCS))
SRCS			+= $(addprefix $(BUILTDIR), $(BUILTSRCS))
OBJS			:= $(addprefix $(BINDIR), $(SRCS:.c=.o))

all : libraries $(NAME)

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

clean:
	@$(MAKE) -C $(LIBFT) fclean
	@echo $(NAME): Deleting binaries.
	@rm -r $(BINDIR)

fclean: clean
	@echo $(NAME): Deleting program.
	@rm -f $(NAME)

re : fclean all