NAME			:= minishell
CFLAGS			:= -Wall -Wextra -Werror -g
VARSRCS			:= get.c set.c
SRCS			:= main.c utils.c debug.c allocator.c minishell.c env.c signals.c
TOKENSRCS		:= token.c list.c free.c expension.c
QUOTESRCS		:= quotes.c quotes_utils.c
BUILTSRCS		:= env.c echo.c pwd.c cd.c unset.c export.c exit.c builtins.c
CMDSRCS			:= commands.c parsing.c pipe.c free.c heredoc.c constructors.c
INCDIR			:= include/
BINDIR			:= bin/
SRCDIR			:= src/
VARDIR			:= vars/
QUOTEDIR		:= quotes/
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
SRCS			+= $(addprefix $(QUOTEDIR), $(QUOTESRCS))
OBJS			:= $(addprefix $(BINDIR), $(SRCS:.c=.o))

all : libraries $(NAME)

debug : CFLAGS += -g -DDEBUG=1

debug : all

animation:
	@i=0; \
	while [ $$i -le 54 ]; do \
	    printf "compiling: /\r"; \
	    sleep 0.1; \
	    printf -- "compiling: -\r"; \
	    sleep 0.1; \
	    printf -- 'compiling: \\\r'; \
	    sleep 0.1; \
	    printf -- "compiling: |\r"; \
	    sleep 0.1; \
	    ((i = i + 1)); \
	done &

$(READLINE)/libreadline.a : 
	@cd $(READLINE) && \
	./configure --prefix=$$PWD > /dev/null 2>&1 && \
	make install > /dev/null 2>&1 && \
	cd ../..

leaks:
	valgrind --track-fds=yes --show-leak-kinds=all --show-reachable=no --trace-children=yes --leak-check=full ./minishell

libft : 
	@$(MAKE) -C $(LIBFT)

libraries : libft $(READLINE)/libreadline.a

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
	@mkdir $(BINDIR)$(QUOTEDIR)

clean:
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -s -C $(READLINE) uninstall > /dev/null 2>&1 
	@$(MAKE) -s -C $(READLINE) clean
	@echo "$(BLUE)$(NAME): $(GREEN)Deleting binaries.$(END_COLOR)"
	@rm -rf $(BINDIR)

fclean: clean
	@echo "$(BLUE)$(NAME): $(GREEN)Deleting program.$(END_COLOR)"
	@rm -f $(NAME)

re : fclean all

.PHONY : re fclean clean all libft leaks libraries readline debug uninstall

# **************************************************************************** #
# Colors

BLACK		=\033[30m
RED			=\033[31m
GREEN		=\033[32m
YELLOW		=\033[33m
BLUE		=\033[34m
PURPLE		=\033[35m
CYAN		=\033[36m
WHITE		=\033[37m

# # Text

ERASE		=\033[2K\r
END_COLOR	=\033[0m
BOLD		=\033[1m
FAINT		=\033[2m
ITALIC		=\033[3m
UNDERLINE	=\033[4m

# # Background

BG_BLACK	=\033[40m
BG_RED		=\033[41m
BG_GREEN	=\033[42m
BG_YELLOW	=\033[43m
BG_BLUE		=\033[44m
BG_PURPLE	=\033[45m
BG_CYAN		=\033[46m
BG_WHITE	=\033[47m

# highlight color

HI=\033[7m
# **************************************************************************** #
