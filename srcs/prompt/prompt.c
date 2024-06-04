/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:38:23 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 12:55:16 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_wspace(char *line, t_ms *ms)
{
	while (1)
	{
		if (is_w_space(line[ms->i]))
			ms->i++;
		else
			break ;
		if (!line[ms->i])
		{
			free(line);
			return (-1);
		}
	}
	return (0);
}

bool	builtins_are_done(t_ms *ms, char **env)
{
	if (count_nb_cmd(ms->parser) == 1)
	{
		if (handle_cd(ms, env, ms->parser) == 1)
			return (true);
		if (handle_exit(ms->parser->cmd, ms, env, ms->parser) == 1)
			return (true);
		if (handle_export(env, 0, ms->parser, ms) == 1)
			return (true);
		if (handle_unset(ms->parser->cmd, env, ms) == 1)
			return (true);
		if (handle_env(ms->parser, env, ms->parser, ms) == 1)
			return (true);
		if (handle_pwd(ms->parser->cmd, ms->parser, ms) == 1)
			return (true);
		if (handle_echo(ms->parser->cmd, ms->parser, ms) == 1)
			return (true);
	}
	return (false);
}

void	prompt2(char *line, int history, char **env, t_ms *ms)
{
	if (line && line[0] != 0)
	{
		add_history(line);
		if (check_wspace(line, ms) == -1)
			return ;
		ms->lh = ft_strjoin_const(line, "\n");
		ft_putstr_fd(ms->lh, history);
		free(ms->lh);
		ms->lexer = lexer(ms, env);
		if (ms->lexer && *ms->lexer)
		{
			parsing(ms);
			ft_free_lexer(ms->lexer);
			ms->lexer = NULL;
			ms->nb_cmd = count_nb_cmd(ms->parser);
			if (!builtins_are_done(ms, env) && ms->parser)
				init_cmd(ms, ms->parser, env);
			ft_free_parser(ms->parser);
			ms->parser = NULL;
		}
	}
}

void	prompt3(t_ms *ms, char *tmp, char *cwd, char **env)
{
	static int	start;

	start = 0;
	while (ms->line || start == 0)
	{
		start++;
		ms->dir = getcwd(cwd, 1024);
		ms->path = find_path(env);
		free(ms->prompt);
		tmp = ft_strjoin_const(cwd, "$ ");
		ms->prompt = ft_strjoin_const(COLOR, tmp);
		free(tmp);
		ms->prompt = ft_strjoin(ms->prompt, R_COLOR);
		parent_sig();
		ms->line = readline((const char *)ms->prompt);
		ms->i = 0;
		free(ms->prompt);
		ms->prompt = NULL;
		child_sig();
		sig(ms);
		prompt2(ms->line, ms->history, env, ms);
		if (ms->path)
			ft_free_tab(ms->path);
		parent_sig();
	}
}

void	prompt(char **env, int history)
{
	char	cwd[1024];
	t_ms	ms;
	int		i;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	ms.history = history;
	ms.prompt = ft_strjoin_const(cwd, "$ ");
	ms.line = NULL;
	ms.fd = NULL;
	ms.e_s = 0;
	ms.dir = NULL;
	ms.tab_bool = malloc(sizeof(bool) * (size_env(env)));
	while (i < size_env(env))
		ms.tab_bool[i++] = false;
	ms.boul = 0;
	ms.file_err = 0;
	if (set_new_env(env) == 0)
	{
		close((free(ms.prompt), free(ms.tab_bool), ms.history));
		return ;
	}
	prompt3(&ms, NULL, cwd, env);
	ft_free_env(&ms, env);
	close((printf("exit\n"), free(ms.prompt), free(ms.tab_bool), ms.history));
}
