/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:36:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/29 13:04:24 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_front_file(t_file **lst, t_file *new)
{
	if (lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else if (new)
		*lst = new;
}

void	infile_actual_dir(t_ms *ms, char *str, t_dir *d)
{
	ms->new_dir = ft_strjoin_const(ms->dir, str + 1);
	if (!ms->new_dir)
		free (ms->new_dir);
	if (access(ms->new_dir, F_OK) == -1)
		exit((free(ms->new_dir), closedir(d->dir), \
			h_d_err(str, 1, NULL), exit_child(ms), \
			ms->e_s = 126, 126));
	if (access(ms->new_dir, R_OK) == -1)
		exit((free(ms->new_dir), closedir(d->dir), \
			h_d_err(str, 3, NULL), exit_child(ms), \
			ms->e_s = 126, 126));
	free(ms->new_dir);
	ms->new_dir = NULL;
}

int	check_last_file(t_file *file)
{
	int	type;

	type = -1;
	while (file)
	{
		if (file->type == LIMITER || file->type == INFILE)
			type = file->type;
		file = file->next;
	}
	return (type);
}

void	close_parser(t_parser *parser)
{
	if (parser->fd[0] != -1)
		close(parser->fd[0]);
	if (parser->fd[1] != -1)
		close(parser->fd[1]);
	if (parser->fdin != 0)
		close(parser->fdin);
	if (parser->fdout != 1)
		close(parser->fdout);
	parser->fdin = 0;
	parser->fdout = 1;
}
