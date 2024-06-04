/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:19:51 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/29 12:03:05 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	infile_back(t_ms *ms, char *str, t_dir *d)
{
	ms->new_dir = going_back(ms->dir);
	if (!ms->new_dir)
		free (ms->new_dir);
	ms->new_dir = ft_strjoin(ms->new_dir, str + 2);
	if (!ms->new_dir)
		free (ms->new_dir);
	if (access(ms->new_dir, F_OK) == -1)
		exit((closedir(d->dir), h_d_err(str, 1, NULL), \
		exit_child(ms), free(ms->new_dir), ms->e_s = 126, 126));
	if (access(ms->new_dir, R_OK) == -1)
		exit((closedir(d->dir), h_d_err(str, 3, NULL), \
		exit_child(ms), free(ms->new_dir), ms->e_s = 126, 126));
	free(ms->new_dir);
	ms->new_dir = NULL;
}

void	check_infile(t_ms *ms, char *str)
{
	t_dir		d;

	d.i = 0;
	ms->new_dir = NULL;
	d.dir = opendir(ms->dir);
	if (d.dir)
	{
		if (str[0] == '/')
		{
			if (access(str, F_OK) == 0)
				exit((closedir(d.dir), h_d_err(str, 2, NULL), \
				exit_child(ms), free(ms->new_dir), ms->e_s = 126, 126));
			else
				h_d_err(str, 1, NULL);
			exit ((exit_child(ms), closedir(d.dir), 127));
		}
		if (ft_strncmp(str, "./", 2) == 0)
			infile_actual_dir(ms, str, &d);
		if (ft_strncmp(str, "../", 3) == 0)
			infile_back(ms, str, &d);
		closedir(d.dir);
	}
	else
		exit ((h_d_err(str, 1, NULL), exit_child(ms), ms->e_s = 127, 127));
}

void	outfile_back(t_ms *ms, char *str, t_dir *d)
{
	struct stat	info;

	ms->new_dir = going_back(ms->dir);
	if (!ms->new_dir)
		free (ms->new_dir);
	ms->new_dir = ft_strjoin(ms->new_dir, str + 2);
	if (!ms->new_dir)
		free (ms->new_dir);
	if (access(ms->new_dir, F_OK) == 0)
	{
		if (access(ms->new_dir, W_OK) == -1)
			exit((free(ms->new_dir), closedir(d->dir), h_d_err(str, 3, NULL), \
				exit_child(ms), ms->e_s = 126, 126));
		else if (stat(str, &info) == 0 && S_ISDIR(info.st_mode))
			exit((free(ms->new_dir), closedir(d->dir), \
			h_d_err(str, 2, NULL), exit_child(ms), ms->e_s = 126, 126));
	}
	free(ms->new_dir);
	ms->new_dir = NULL;
}

void	outfile_actual_dir(t_ms *ms, char *str, t_dir *d)
{
	struct stat	info;

	if (ft_strncmp(str, "./", 2) == 0)
		ms->new_dir = ft_strjoin(ms->new_dir, str + 2);
	else
		ms->new_dir = ft_strjoin(ms->new_dir, str);
	if (!ms->new_dir)
	{
		free (ms->new_dir);
		ms->new_dir = NULL;
	}
	if (access(ms->new_dir, F_OK) == 0)
	{
		if (access(ms->new_dir, W_OK) == -1)
			exit((closedir(d->dir), h_d_err(str, 3, NULL), \
				free(ms->new_dir), exit_child(ms), ms->e_s = 1, 1));
		else if (stat(str, &info) == 0 && S_ISDIR(info.st_mode))
			exit((free(ms->new_dir), closedir(d->dir), \
			h_d_err(str, 2, NULL), exit_child(ms), ms->e_s = 126, 126));
	}
	free(ms->new_dir);
	ms->new_dir = NULL;
}

void	check_outfile(t_ms *ms, char *str)
{
	t_dir		d;

	d.i = 0;
	ms->new_dir = NULL;
	d.dir = opendir(ms->dir);
	if (d.dir)
	{
		if (str[0] == '/')
		{
			if (access(str, F_OK) == 0)
				exit((closedir(d.dir), h_d_err(str, 2, NULL), \
				exit_child(ms), ms->e_s = 126, 126));
			else
				h_d_err(str, 1, NULL);
			exit ((closedir(d.dir), 127));
		}
		if (ft_strncmp(str, "./", 2) == 0 || str[0] != '/' || str[0] != '.')
			outfile_actual_dir(ms, str, &d);
		if (ft_strncmp(str, "../", 3) == 0)
			outfile_back(ms, str, &d);
		closedir(d.dir);
	}
	else
		exit ((h_d_err(str, 1, NULL), exit_child(ms), ms->e_s = 127, 127));
}
