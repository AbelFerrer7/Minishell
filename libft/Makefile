LIB = ar rcs
RM = rm -f

CC = cc
CCFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC =	ft_memset.c ft_bzero.c ft_strlen.c ft_atoi.c ft_isdigit.c ft_isalpha.c\
ft_isprint.c ft_isascii.c ft_isalnum.c ft_memchr.c ft_memcpy.c ft_memcmp.c\
ft_memmove.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_calloc.c\
ft_strncmp.c ft_toupper.c ft_tolower.c ft_strnstr.c ft_strrchr.c ft_substr.c\
ft_strtrim.c ft_strjoin.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strstr.c\
ft_strcmp.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)
BONUSOBJ = $(BONUS:.c=.o)
INCLUDE = libft.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(LIB) $(NAME) $(OBJ)

bonus: .bonus

.bonus: $(OBJ) $(BONUSOBJ) $(INCLUDE)
	$(LIB) $(NAME) $(OBJ) $(BONUSOBJ)
	@touch .bonus

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(BONUSOBJ)
	$(RM) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
