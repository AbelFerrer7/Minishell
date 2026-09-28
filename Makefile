NAME    = minishell
SRCDIR  = src
INCDIR  = include
OBJDIR  = obj

SRCS    = minishell.c parsing/parsing.c parsing/parsing_pipes.c parsing/parsing_cmd.c \
		  parsing/parsing_args.c parsing/parsing_redirects.c parsing/parsing_syntax.c \
		  parsing/parsing_redirects_stx.c memory.c environment.c elim_env.c expand_vars.c \
		  expand_utils.c execution/execute.c execution/execute_utils.c \
		  execution/execute_utils2.c execution/execute_pipes.c execution/execute_builtins_cmd.c \
		  execution/execute_cmd.c redirects/redirects.c redirects/redirects_parser.c \
		  redirects/redirects_handlers.c redirects/redirects_extract.c utils.c utils2.c \
		  signals.c builtins/builtins.c builtins/builtin_utils.c \
		  builtins/builtin_cd.c builtins/cd_utils.c builtins/builtins_exit.c builtins/builtins_utils.c \
		  builtins/builtins_export.c builtins/export_utils.c

OBJS    = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I$(INCDIR) -Ilibft
RM      = rm -f
LIBDIR  = libft
LIBS    = -lft

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBDIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBDIR) -lreadline $(LIBS) -o $(NAME)

$(LIBDIR)/libft.a:
	$(MAKE) -C $(LIBDIR)

clean:
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re

