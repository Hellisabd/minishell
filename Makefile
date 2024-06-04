NAME	= minishell


DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
ORANGE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m


SRCS	= 	srcs/parsing/parsing.c \
			srcs/parsing/quote_gest.c \
			srcs/parsing/quote_gest2.c \
			srcs/parsing/parsing_utils.c \
			srcs/lexer/lexer.c \
			srcs/lexer/lexer_utils.c \
			srcs/lexer/add_spaces.c \
			srcs/lexer/token.c	\
			srcs/lexer/ft_split_lexer.c \
			srcs/files/fds_gest.c \
			srcs/files/file_gest.c \
			srcs/files/file_utils.c \
			srcs/files/check_infile.c \
			srcs/delete_things/delete_lists.c \
			srcs/delete_things/exit_child.c \
			srcs/prompt/prompt.c	\
			srcs/cmd/pipex.c	\
			srcs/cmd/cmd.c	\
			srcs/cmd/first_cmd.c	\
			srcs/cmd/last_cmd.c \
			srcs/cmd/mid_cmd.c \
			srcs/cmd/dir.c \
			srcs/builtins/exit.c \
			srcs/builtins/cd.c \
			srcs/builtins/echo.c \
			srcs/builtins/env.c \
			srcs/builtins/pwd.c \
			srcs/builtins/unset.c \
			srcs/builtins/export.c \
			srcs/builtins/utils.c \
			srcs/builtins/utils2.c \
			srcs/builtins/utils_export.c \
			srcs/variables/env_variables.c \
			srcs/variables/expand.c	\
			srcs/variables/expand_utils.c \
			srcs/variables/expand_utils2.c \
			srcs/err_gest.c \
			srcs/signal/signal.c \
			srcs/signal/handlers.c


SRCS_MAIN	= main.c $(SRCS)

OBJS	= $(SRCS_MAIN:.c=.o)

CC	= @cc

CFLAGS	+= -Wall -Wextra -Werror   -g3

RM	= @rm -rf

CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M:%S")

all	: $(NAME)

$(NAME) : $(OBJS)
	@make --no-print-directory -C Libft 
	$(CC) $(CFLAGS)  $(OBJS) -lreadline -lncurses Libft/libft.a $(LIBS) -o $(NAME)
	@echo "$(MAGENTA)Make Done$(DEF_COLOR)"

clean : 
	$(RM) $(OBJS) 
	@make --no-print-directory -C Libft clean
	@echo "$(ORANGE)OBJS CLEAR MY FRIEND!$(DEF_COLOR)"

fclean : 
	$(RM) $(NAME) $(OBJS)
	@make --no-print-directory -C Libft fclean
	@echo "$(MAGENTA)¯|_(ツ)_/¯ I'M SO PROUD OF U!$(DEF_COLOR)"


re :	fclean all

ex :	all clean val

valfd :
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑ALL FINE!(•̀ᴗ•́)و$(DEF_COLOR)"
	@echo "$(CYAN)(☞ﾟ∀ﾟ)☞ TYPE URE THINGS(☞ﾟ∀ﾟ)☞$(DEF_COLOR)"
	@valgrind --track-fds=yes --leak-check=full --quiet ./minishell

val :
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑ALL FINE!(•̀ᴗ•́)و$(DEF_COLOR)"
	@echo "$(CYAN)(☞ﾟ∀ﾟ)☞ TYPE URE THINGS(☞ﾟ∀ﾟ)☞$(DEF_COLOR)"
	@valgrind -s --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --trace-children=yes --gen-suppressions=all --suppressions=valgrind.supp --quiet ./minishell
san : $(OBJS)
	@make --no-print-directory -C Libft 
	$(CC) $(FFLAGS)  $(OBJS) -lreadline Libft/libft.a $(LIBS) -o $(NAME)
	@echo "$(MAGENTA)Make Done$(DEF_COLOR)"
	@./minishell

git	: fclean
	@$(RM) */a.out a.out
	@git add . > /dev/null 2>&1
	@@msg=$${MSG:-"main $(CURRENT_DATE)"}; git commit -m "$$msg main $(CURRENT_DATE)" > /dev/null 2>&1 
	@git push > /dev/null 2>&1
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑GIT UPDATE!(•̀ᴗ•́)و ̑̑$(DEF_COLOR)"
