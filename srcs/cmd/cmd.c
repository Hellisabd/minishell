/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:01:09 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/28 16:06:39 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_here_doc(t_parser *parser, t_ms *ms)
{
	while (parser)
	{
		parser->tmp = parser->file;
		if (parser && parser->file && parser->file->type == LIMITER)
			open_heredoc(ms, parser, &parser->tmp);
		parser = parser->next;
	}
}

void	init_cmd2(t_ms *ms, t_parser **tmp, char **env)
{
	open_here_doc(*tmp, ms);
	if (ms->nb_cmd > 1)
	{
		first_command(ms, *tmp, env);
		ms->i++;
		*tmp = (*tmp)->next;
	}
	while (ms->i < ms->nb_cmd - 1)
	{
		all_cmd_gest(ms, *tmp, env);
		ms->i++;
		(*tmp) = (*tmp)->next;
	}
}

int	count_nb_cmd(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		parser = parser->next;
		i++;
	}
	return (i);
}

void	end_cmd(t_ms *ms, t_parser *tmp, int status)
{
	ms->i = 1;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		exit_end(status, ms);
		tmp = tmp->next;
	}
	ms->i = 0;
	close_all_fds(ms->parser, ms);
}

void	init_cmd(t_ms *ms, t_parser *parser, char **env)
{
	t_parser	*tmp;
	int			status;

	tmp = parser;
	status = 126;
	ms->i = 0;
	if (ms->nb_cmd > 1)
	{
		ms->fd = malloc(sizeof(int *) * (ms->nb_cmd));
		while (ms->i < ms->nb_cmd - 1)
		{
			ms->fd[ms->i] = malloc(sizeof(int) * 2);
			pipe(ms->fd[ms->i]);
			ms->i++;
		}
		ms->fd[ms->i] = NULL;
	}
	else
		ms->fd = NULL;
	ms->i = 0;
	init_cmd2(ms, &tmp, env);
	last_cmd_gest(ms, tmp, parser, env);
	end_cmd(ms, parser, status);
}
