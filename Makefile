NAME			:= minishell
CFLAGS			:= -Wall -Wextra -Werror -g
SRCS			:= main.c utils.c debug.c allocator.c minishell.c env.c
VARSRCS			:= get.c set.c
TOKENSRCS		:= token.c list.c free.c quotes.c
SRCS			:= main.c utils.c debug.c allocator.c minishell.c env.c
TOKENSRCS		:= token.c list.c free.c quotes.c expension.c
BUILTSRCS		:= env.c echo.c pwd.c cd.c unset.c export.c exit.c builtins.c
CMDSRCS			:= commands.c parsing.c pipe.c free.c heredoc.c constructors.c
INCDIR			:= include/
BINDIR			:= bin/
SRCDIR			:= src/
VARDIR			:= vars/
TOKENDIR		:= token/
BUILTDIR		:= builtins/
CMDSDIR			:= commands/
LIBFT			:= lib/libft/
READLINE		:= lib/readline/
RM				:= rm -f
HEADERS			:= -I ./include -I $(LIBFT)/include -I $(READLINE)/include
CC				:= gcc
LIBS			:= $(LIBFT)/libft.a $(READLINE)/libreadline.a $(READLINE)/libhistory.a
SRCS			+= $(addprefix $(TOKENDIR), $(TOKENSRCS))
SRCS			+= $(addprefix $(BUILTDIR), $(BUILTSRCS))
SRCS			+= $(addprefix $(VARDIR), $(VARSRCS))
SRCS			+= $(addprefix $(CMDSDIR), $(CMDSRCS))
OBJS			:= $(addprefix $(BINDIR), $(SRCS:.c=.o))

all : libraries $(NAME)

readline :
	cd $(READLINE) && \
	./configure --prefix=$$PWD && \
	make install

leaks:
	valgrind --track-fds=yes --show-leak-kinds=all --show-reachable=no --trace-children=yes --leak-check=full ./minishell

libft : 
	@$(MAKE) -C $(LIBFT)

libraries : libft readline
	@$(MAKE) -C $(LIBFT)

$(BINDIR)%.o : $(SRCDIR)%.c
	@$(CC) -c $(CFLAGS) -o $@ $^ $(HEADERS)

$(NAME) : $(BINDIR) $(OBJS)
	@echo $(NAME): Compiling!
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(HEADERS) -lncurses

$(BINDIR) :
	@mkdir $(BINDIR)
	@mkdir $(BINDIR)$(TOKENDIR)
	@mkdir $(BINDIR)$(BUILTDIR)
	@mkdir $(BINDIR)$(VARDIR)
	@mkdir $(BINDIR)$(CMDSDIR)

clean:
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(READLINE) uninstall
	@$(MAKE) -C $(READLINE) clean
	@echo $(NAME): Deleting binaries.
	@rm -r $(BINDIR)

fclean: clean
	@echo $(NAME): Deleting program.
	@rm -f $(NAME)

re : fclean all