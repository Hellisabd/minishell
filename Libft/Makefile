
NAME		=	libft.a

SRCS		=	ft_isalpha.c	\
			ft_strlen.c	\
			ft_isprint.c	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_strncmp.c	\
			ft_strndup.c	\
			ft_uitoa.c	\
			ft_strchr.c	\
			ft_strrchr.c	\
			ft_bzero.c	\
			ft_strnstr.c	\
			ft_strlcat.c	\
			ft_memset.c	\
			ft_memcpy.c	\
			ft_memchr.c	\
			ft_memmove.c	\
			ft_memcmp.c	\
			ft_atoi.c	\
			ft_strjoin.c	\
			ft_itoa.c	\
			ft_strdup.c	\
			ft_strlcpy.c	\
			ft_calloc.c	\
			ft_substr.c	\
			ft_strtrim.c	\
			ft_strmapi.c	\
			ft_striteri.c	\
			ft_split.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putnbr_fd.c	\
			ft_putendl_fd.c	\
			ft_itoa_base.c	\
			ft_itoa_base_uintptr_t.c \
			ft_printf.c	\
			ft_printnbr.c	\
		  	ft_prints.c		\
			ft_lstnew.c		\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c		\
			ft_free_double_tab.c \
			get_next_line.c \
			find_first_c.c	\
			ft_get_ppid.c	\
			ft_free_triple_tab.c \
			ft_strstartdup.c	\
			ft_sort_tab_int.c	\
			ft_epur_str.c



OBJS		=	$(SRCS:.c=.o)

CC		=	@gcc

CFLAGS		+= 	-Wall -Wextra -Werror -g3

RM		=	rm -f

all		:	
	@make --no-print-directory $(NAME)

$(NAME)		:	$(OBJS)
	@ar -crs $(NAME) $(OBJS)
clean		:	
	@$(RM) $(OBJS)

fclean		:	
	@$(RM) $(NAME) $(OBJS)

re		:	fclean all

ex		:	fclean all clean

