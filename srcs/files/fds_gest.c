/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_gest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:01:54 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/29 14:09:58 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(t_parser *parser, t_ms *ms)
{
	int	i;

	i = -1;
	if (ms->fd)
	{
		while (*ms->fd && ms->fd[++i])
		{
			if (ms->fd[i][0] != -1)
				close(ms->fd[i][0]);
			if (ms->fd[i][1] != -1)
				close(ms->fd[i][1]);
			ms->fd[i][0] = -1;
			ms->fd[i][1] = -1;
		}
		ft_free_tab_int(ms->fd);
		ms->fd = NULL;
	}
	while (parser)
	{
		close_parser(parser);
		parser = parser->next;
	}
}

void	open_heredoc(t_ms *ms, t_parser *parser, t_file **tmp)
{
	int			status;

	status = 0;
	pipe(parser->fd);
	if (parser->fdin < 0)
		printf("Probleme\n");
	ms->pid1 = fork();
	if (ms->pid1 < 0)
		exit ((ft_free_tab(ms->path), close_fd(ms->parser, ms), \
		perror("Error"), 1));
	if (ms->pid1 == 0)
		real_heredoc(parser, tmp, ms);
	else
	{
		passive_sig();
		close(parser->fd[1]);
		waitpid(ms->pid1, &status, 0);
		child_sig();
		exit_end(status, ms);
		parser->fdin = 0;
		return ;
	}
	child_sig();
	return ;
}

void	open_files2(t_ms *ms, t_file *tmp, t_parser *p)
{
	if (tmp->type == OUTFILE2)
	{
		if (p->fdout != 1)
			close(p->fdout);
		check_outfile(ms, tmp->filename);
		p->fdout = open(tmp->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (tmp->type == OUTFILE)
	{
		if (p->fdout != 1)
			close(p->fdout);
		check_outfile(ms, tmp->filename);
		p->fdout = open(tmp->filename, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	}
	if (p->fdout == -1)
	{
		if (access(tmp->filename, F_OK) == -1)
			exit ((h_d_err(tmp->filename, 1, NULL), exit_child(ms), 1));
		if (!tmp->next)
			exit ((h_d_err(tmp->filename, 3, NULL), exit_child(ms), 1));
		h_d_err((ms->e_s = 1, tmp->filename), 3, NULL);
	}
}

void	open_files(t_ms *ms, t_parser *parser)
{
	t_file	*tmp;

	tmp = parser->file;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			if (parser->fdin != 0)
				close(parser->fdin);
			check_infile(ms, tmp->filename);
			parser->fdin = open(tmp->filename, O_RDONLY, 0777);
		}
		if (parser->fdin == -1)
			exit ((h_d_err(tmp->filename, 1, NULL), exit_child(ms), \
			ft_free_tab(ms->path), 1));
		open_files2(ms, tmp, parser);
		tmp = tmp->next;
	}
}

void	close_all_fds(t_parser *parser, t_ms *ms)
{
	while (parser)
	{
		close_fd(ms->parser, ms);
		parser = parser->next;
		ms->i++;
	}
}
