SRCS	= ft_isalpha.c \
		ft_isdigit.c ft_isascii.c ft_isalnum.c ft_isalnum.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_strdup.c \
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_atoi.c ft_calloc.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c \
		ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_printf.c \
		ft_putaddr_fd.c ft_putuint_fd.c ft_revbits.c ft_puthex_fd.c \
		ft_getnextline.c
OBJS		= $(addprefix $(BINDIR), $(SRCS:.c=.o))
NAME		= libft.a
INCDIR		= include/
BINDIR		= bin/
SRCDIR		= src/
LIBC		= ar rcs
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -f
CC			= gcc

all : $(NAME)

$(BINDIR)%.o : $(SRCDIR)%.c
	@$(CC) -c $(CFLAGS) -o $@ $^ -I $(INCDIR)

$(NAME) : $(BINDIR) $(OBJS)
	@echo LIBFT: Creating library.
	@$(LIBC) $@ $(OBJS)

$(BINDIR) :
	@mkdir $(BINDIR)

clean :
	@echo "$(BLUE)LIBFT: $(GREEN)Clearing binaries$(END_COLOR)"
	@$(RM) -r $(BINDIR)

fclean : clean
	@echo "$(BLUE)LIBFT: $(GREEN)Deleting library.$(END_COLOR)"
	@$(RM) $(NAME)

re : fclean all

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