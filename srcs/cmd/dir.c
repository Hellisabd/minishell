/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:59:55 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 13:50:55 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	is_dir2(t_ms *ms, char *str, t_dir d)
{
	struct stat	info;

	ms->new_dir = ft_strjoin_const(ms->dir, str + 1);
	if (!ms->new_dir)
		free (ms->new_dir);
	if (stat(str, &info) == 0)
		if (!S_ISDIR(info.st_mode) && access(ms->new_dir, F_OK) == 0)
			exit((free(ms->new_dir), closedir(d.dir), \
			h_d_err(str, 3, NULL), exit_child(ms), ms->e_s = 126, 126));
	if (access(ms->new_dir, F_OK) == 0)
	{
		free(ms->new_dir);
		closedir(d.dir);
		h_d_err(str, 2, NULL);
		exit((exit_child(ms), 126));
	}
	else
		h_d_err(str, 1, NULL);
	exit ((exit_child(ms), free(ms->new_dir), closedir(d.dir), 127));
}

void	is_dir3(t_ms *ms, char *str, t_dir d)
{
	struct stat	info;

	ms->new_dir = going_back(ms->dir);
	if (!ms->new_dir)
		free (ms->new_dir);
	ms->new_dir = ft_strjoin(ms->new_dir, str + 2);
	if (!ms->new_dir)
		free (ms->new_dir);
	if (stat(str, &info) == 0)
		if (!S_ISDIR(info.st_mode) && access(str, F_OK) == 0)
			exit((free(ms->new_dir), closedir(d.dir), \
			h_d_err(str, 3, NULL), exit_child(ms), ms->e_s = 126, 126));
	if (access(ms->new_dir, F_OK) == 0)
		exit((free(ms->new_dir), closedir(d.dir), \
		h_d_err(str, 2, NULL), exit_child(ms), ms->e_s = 126, 126));
	else
		h_d_err(str, 1, NULL);
	exit ((exit_child(ms), free(ms->new_dir), closedir(d.dir), 127));
}

void	is_dir(t_ms *ms, char *str)
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
				exit((closedir(d.dir), h_d_err(str, 2, NULL), exit_child(ms), \
				ms->e_s = 126, 126));
			else
				h_d_err(str, 1, NULL);
			exit ((exit_child(ms), closedir(d.dir), 127));
		}
		if (ft_strncmp(str, "./", 2) == 0)
			is_dir2(ms, str, d);
		if (ft_strncmp(str, "../", 3) == 0)
			is_dir3(ms, str, d);
		closedir(d.dir);
	}
	else
		exit ((h_d_err(str, 1, NULL), exit_child(ms), ms->e_s = 127, 127));
}
