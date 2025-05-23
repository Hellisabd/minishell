/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:31:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/04/12 13:18:29 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "get_next_line.h"
# include "../minishell.h"
# include <stdio.h>

typedef struct s_marche{
	int		j;
	int		h;
	size_t	i;
	int		sign;
	int		div;
	int		max_rank;
	int		div_max;
	int		actual;
}	t_m;

typedef struct Node
{
	int				nbr;
	struct Node		*next;
	int				rank;
	char			*str;
}	t_Node;

int		ft_lstsize(t_Node *lst);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_free_tab(char **tab);
void	ft_free_triple_tab(char ***cmd);
void	ft_lstiter(t_Node *list, void (*f)(int));
void	ft_lstadd_back(t_Node **lst, t_Node *new);
void	ft_lstadd_front(t_Node **lst, t_Node *new);
void	ft_lstdelone(t_Node *lst);
void	ft_lstclear(t_Node **lst);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	count_words_isspace(char *s);
void	ft_free_tab_int(int **tab);
char	find_first_c(char *str, char c2, char c1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *line, char *buff);
char	*ft_strjoin_const(const char *line, char *buff);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
char	*ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(char *s);
char	*ft_itoa_base_uintptr_t(uintptr_t n);
char	*ft_itoa_base(int n, int low_or_up);
char	*ft_uitoa(unsigned int n);
size_t	ft_strlen(char *s);
size_t	count_words(char *s, char c);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
size_t	ft_strlcat(char *dst, char *src, size_t size);
t_Node	*ft_lstmap(t_Node *lst, int (*f)(int), void (*del)(int));
t_Node	*ft_lstnew(int number);
t_Node	*ft_lstlast(t_Node *lst);
int		ft_printf(const char *str, ...);
int		ft_printnbr(int n);
int		ft_prints(char *s);
int		ft_printp(uintptr_t n);
int		ft_printhexlow(unsigned int n);
int		ft_printhexup(unsigned int n);
int		ft_printchar(int c);
int		ft_printunbr(unsigned int n);
ssize_t	ft_atoi(const char *nptr);
int		ft_getppid(char *path_file);
char	*fill_dest(char *s, t_m *var);
int		free_split(char **res, int j);
char	*ft_strstartdup(char *s, int start);
char	*ft_strndup(char *s, int n);
void	ft_free_spec_tab(char **tab, int size);
int		ft_strisdigit(char *s);
char	*ft_epur_str(char *s, char c);

#endif
