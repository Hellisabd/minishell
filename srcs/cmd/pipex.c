/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:44:48 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/30 17:39:21 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_cmd(t_ms *ms, t_parser *parser, char **env)
{
	char	*tmp;
	int		j;
	int		blank;

	j = 0;
	blank = 0;
	while (parser->cmd && parser->cmd[blank] && parser->cmd[blank][0] == '\0')
		blank++;
	close(ms->history);
	free(ms->prompt);
	close_fd(ms->parser, ms);
	check_cmd(ms, parser, env, blank);
	while (ms->path && ms->path[j])
	{
		tmp = ft_strjoin(ms->path[j], parser->cmd[blank]);
		ms->path[j] = NULL;
		if (access(tmp, F_OK) == 0)
			if (access(tmp, X_OK) == 0)
				execve(tmp, parser->cmd + blank, env);
		free (tmp);
		j++;
	}
	is_dir(ms, parser->cmd[0]);
	command_err(parser->cmd[0], ms, parser);
}

void	exit_end(int status, t_ms *ms)
{
	if (WIFEXITED(status))
		ms->e_s = WEXITSTATUS(status);
	else if (status <= 255 && status >= 0)
	{
		ms->e_s = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
		ms->e_s = g_e_s;
}

int	count_here(t_file *tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp->type == LIMITER)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	execute_heredoc(t_ms *ms, char *tmp, t_file **file, t_parser *origin)
{
	(void)origin;
	while (1)
	{
		tmp = get_next_line(0);
		if (g_e_s == 130)
			exit ((close(ms->history), exit_child(ms), free(tmp), 130));
		if (!tmp)
			exit ((ft_putstr_fd \
			("mini: warning: here-document delimited by end-of-file\n", 2), \
			close_fd(ms->parser, ms), ft_free_parser(ms->parser), \
				ft_free_tab(ms->path), free(tmp), 0));
		if (0 == ft_strncmp((*file)->filename, tmp, \
		ft_strlen((*file)->filename)))
			if (tmp[ft_strlen((*file)->filename)] == '\n')
				exit ((close_fd(ms->parser, ms), ft_free_parser(ms->parser), \
				ft_free_tab(ms->path), free(tmp), 0));
		ft_putstr_fd(tmp, 1);
		free(tmp);
	}
}

void	real_heredoc(t_parser *origin, t_file **file, t_ms *ms)
{
	char		*tmp;
	int			c;
	t_parser	*parser;
	int			i;

	i = 0;
	tmp = NULL;
	parser = origin;
	free(ms->tab_bool);
	close((ms->tab_bool = NULL, ms->history));
	here_doc_sig();
	c = count_here(parser->file);
	while (i < c - 1)
	{
		trash_here_doc(ms, parser->file->filename, tmp);
		i++;
		*file = (*file)->next;
	}
	if (dup2(parser->fd[1], STDOUT_FILENO) < 0)
		exit (1);
	close(parser->fd[0]);
	close(parser->fd[1]);
	execute_heredoc(ms, tmp, file, origin);
	exit ((close_fd(ms->parser, ms), free_file(parser->file), \
	ft_free_parser(parser), ft_free_tab(ms->path), 130));
}
