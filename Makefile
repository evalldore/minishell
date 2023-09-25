NAME			:= minishell
CFLAGS			:= -Wall -Wextra -Werror
SRCS			:= main.c
INCDIR			:= include/
BINDIR			:= bin/
SRCDIR			:= src/
LIBFT			:= ./lib/libft
OBJS			:= $(addprefix $(BINDIR), $(SRCS:.c=.o))
RM				:= rm -f
HEADERS			:= -I ./include -I $(LIBFT)/include
CC				:= gcc
LIBS			:= $(LIBFT)/libft.a

all : libraries $(NAME)

libraries:
	@$(MAKE) -C $(LIBFT)

$(BINDIR)%.o : $(SRCDIR)%.c
	@$(CC) -c $(CFLAGS) -o $@ $^ $(HEADERS)

$(NAME) : $(BINDIR) $(OBJS)
	@echo $(NAME): Compiling!
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(HEADERS) -lreadline

$(BINDIR) :
	@mkdir $(BINDIR)

clean:
	@$(MAKE) -C $(LIBFT) fclean
	@echo $(NAME): Deleting binaries.
	@rm -r $(BINDIR)

fclean: clean
	@echo $(NAME): Deleting program.
	@rm -f $(NAME)

re : fclean all