/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:17:01 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/30 13:56:11 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR "\001\e[1;91m\002"
# define R_COLOR "\001\e[0m\002"
# define STATUS_FILE "/proc/self/status"
# define PAR 1
# define QUOTE 2
# define DB_QUOTE 3
# define WORD 4
# define PIPE 5
# define AND 6
# define OR 7
# define SINGLE_LEFT 8
# define SINGLE_RIGHT 9
# define INFILE 10
# define OUTFILE 11
# define CMD 12
# define DOUBLE_RIGHT 13
# define HEREDOC 14
# define LIMITER 15
# define FILE_DOOMED 16
# define OUTFILE2 17
# define BLANK 18

# define NC "\e[0m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define ORANGE "\e[1;34m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;36m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include "Libft/libft.h"

typedef struct s_file
{
	char			*filename;
	int				fd;
	int				type;
	struct s_file	*next;
}	t_file;

typedef struct s_parser
{
	char			**cmd;
	t_file			*file;
	t_file			*tmp;
	int				open_out;
	int				fdin;
	int				fdout;
	int				inquote;
	int				*tab;
	int				file_err;
	int				fd[2];
	int				pid;
	struct s_parser	*next;
}	t_parser;

typedef struct s_lexer
{
	char			*str;
	int				token;
	int				err;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_expand
{
	int		i;
	int		j;
	char	*line;
	char	*tmp;
	int		size;
	int		stock;
}	t_expand;

typedef struct s_export
{
	char			*var;
	int				ranked;
	int				rank;
	struct s_export	*next;
}	t_export;

typedef struct s_dir
{
	struct dirent	*in;
	DIR				*dir;
	char			*tmp_dir;
	char			**tab;
	int				i;
}	t_dir;

typedef struct s_ms
{
	t_lexer		**lexer;
	t_parser	*parser;
	char		*line;
	char		*lh;
	char		*prompt;
	char		**path;
	char		*dir;
	char		*old_dir;
	char		*new_dir;
	char		*tmp;
	char		*tmp1;
	int			**fd;
	int			i;
	int			b;
	int			n;
	int			pid1;
	int			*pid;
	int			boul;
	int			nb_cmd;
	int			quote;
	int			db_quote;
	int			par;
	int			history;
	int			*status;
	int			file_err;
	int			e_s;
	bool		*tab_bool;
}	t_ms;

extern long long	g_e_s;

// PROMPT

void	prompt(char **env, int history);

// LEXER

int		size_tab(char **tab);
int		is_w_space(char line);
t_lexer	**lexer(t_ms *ms, char **env);
void	ft_add_back_lexer(t_lexer **lexer, char *str);
int		inside_thing(char *line, int size, t_ms *ms);
char	**ft_split_lexer(char *s);
int		get_token(t_lexer **lexer, t_ms *ms);
void	printlist(t_lexer *node);
void	ft_add_spaces_everywhere(char *our_line, t_ms *ms, int *i, int *j);
void	ft_add_spaces_brackets(char *our_line, t_ms *ms, int *j);
void	ft_add_space(char *our_line, t_ms *ms);
int		in_gest(char **cmd, int i, char c, t_parser *parser);
char	*in_gest_str(char *cmd, char c, t_ms *ms);
char	*remove_quote_str(char *str, t_ms *ms);

// PARSING

void	parsing(t_ms *ms);
void	ft_add_back_parser(t_parser **parser, t_parser *new);
char	**find_path(char **env);
void	printparser(t_parser *node);

//FILES

void	file_gest(t_lexer *lexer, t_parser **parser);
void	ft_lstadd_front_file(t_file **lst, t_file *new);
void	open_files(t_ms *ms, t_parser *parser);
void	free_file(t_file *file);
void	trash_here_doc(t_ms *ms, char *limiter, char *tmp);
void	open_heredoc(t_ms *ms, t_parser *parser, t_file **tmp);
void	real_heredoc(t_parser *parser, t_file **file, t_ms *ms);
void	infile_actual_dir(t_ms *ms, char *str, t_dir *d);
int		check_last_file(t_file *file);

// CMD

void	exec_cmd(t_ms *ms, t_parser *parser, char **env);
void	init_cmd(t_ms *ms, t_parser *parser, char **env);
int		count_nb_cmd(t_parser *parser);
void	all_cmd_gest(t_ms *ms, t_parser *tmp, char **env);
void	init_cmd2(t_ms *ms, t_parser **tmp, char **env);
void	last_cmd_gest(t_ms *ms, t_parser *tmp, t_parser *parser, char **env);
void	dup_gest(t_parser *tmp, t_ms *ms);
void	first_command_dup_gest(t_ms *ms, t_parser *gest);
void	first_command(t_ms *ms, t_parser *gest, char **env);
void	check_cmd(t_ms *ms, t_parser *parser, char **env, int blank);
void	exec_cmd(t_ms *ms, t_parser *parser, char **env);

// DELETE
void	close_fd(t_parser *parser, t_ms *ms);
void	close_all_fds(t_parser *parser, t_ms *ms);
void	exit_child(t_ms *ms);
void	ft_free_parser(t_parser *parser);
void	free_exlist(t_export *ex);
void	ft_free_lexer(t_lexer **lexer);
void	cd_err(char *cmd, char *err, int b);
void	h_d_err(char *infile, int n, char *line);
void	exit_err(char *cmd, char *arg, char *err, int b);
void	command_err(char *cmd, t_ms *ms, t_parser *parser);
int		pipe_err(t_lexer *lexer);
void	ft_free_env(t_ms *ms, char **env);
void	close_parser(t_parser *parser);

// ENVIRONMENT VARIABLES
int		set_new_env(char **env);
int		size_env(char **env);
char	*verif_dollar(char *str, char **env, t_ms *ms);
int		size_expand(char *cmd, int n);
int		search_env(char *cmd, char **env, int size);
void	dollar_dollar(t_ms *ms, t_expand *ex);
void	dollar_question(t_expand *ex, t_ms *ms);
void	dollar_stuff(char **env, char *cmd, t_expand *ex);
void	expandables4(t_expand *ex);
bool	*new_tabool(char **env, bool *tab);
void	lol(int i);

// BUILTINS
int		handle_exit(char **cmd, t_ms *ms, char **env, t_parser *parser);
int		handle_pwd(char **cmd, t_parser *parser, t_ms *ms);
int		handle_cd(t_ms *ms, char **env, t_parser *curent_cmd);
int		handle_env(t_parser *pa, char **env, t_parser *parser, t_ms *ms);
int		handle_echo(char **cmd, t_parser *parser, t_ms *ms);
int		handle_export(char **env, int i, t_parser *parser, t_ms *ms);
int		handle_unset(char **cmd, char **env, t_ms *ms);
int		parse_export(char *s);
int		same_char(char *str1, char *str2);
int		replace(char **cmd, char **env, int i, t_ms *ms);
int		search_and_replace(char *cmd, char **env);
int		new_var(char **cmd, char **env, int i, t_ms *ms);
int		print_export(char **env);
void	is_dir2(t_ms *ms, char *str, t_dir d);
void	is_dir3(t_ms *ms, char *str, t_dir d);
void	is_dir(t_ms *ms, char *str);
void	check_infile(t_ms *ms, char *str);
void	check_outfile(t_ms *ms, char *str);
char	*going_forward(char *dir, char *cmd);
char	*going_back(char *dir);
char	*find_home(char **env);
void	actual_pwd(char *str, char **env, t_ms *ms, int i);
int		handle_echo3(char **cmd, char *s, int i);
int		join_echo(char **cmd, char **s, int i);

// SIGNALS

void	parent_sig(void);
void	child_sig(void);
void	passive_sig(void);
void	here_doc_sig(void);
void	exit_end(int status, t_ms *ms);
void	sig_wait(void);
void	child(int signum);
void	parent(int signum);
void	sig(t_ms *ms);
void	h_s(int signum);

//PROUT.V2

void	pid(void);

#endif