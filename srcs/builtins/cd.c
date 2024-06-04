/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:26:57 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 12:53:10 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_cd4(t_ms *ms)
{
	struct stat	info;

	ms->e_s = 1;
	if (access(ms->parser->cmd[1], F_OK) != 0)
		cd_err(ms->parser->cmd[1], "No such file or directory\n", 1);
	if (stat(ms->parser->cmd[1], &info) == 0)
	{
		if (S_ISDIR(info.st_mode) && access(ms->parser->cmd[1], F_OK) == 0)
			cd_err(ms->parser->cmd[1], "Permission denied\n", 1);
		else if (!S_ISDIR(info.st_mode))
			cd_err(ms->parser->cmd[1], "Not a directory\n", 1);
	}
}

int	handle_cd3(t_ms *ms, char **env, char **tab, int *i)
{
	char		*tmp;

	tmp = NULL;
	if (chdir(tab[(*i)]) != -1)
	{
		if (ms->dir[ft_strlen(ms->dir) - 1] != '/')
			tmp = ft_strjoin_const(ms->dir, "/");
		tmp = ft_strjoin(tmp, tab[(*i)]);
		if (!tmp)
			return (-1);
		return (actual_pwd(tmp, env, ms, 0), free(tmp), 1);
	}
	ms->new_dir = going_forward(ms->dir, tab[(*i)]);
	if (!ms->new_dir)
		return (-1);
	if (chdir(ms->new_dir) == -1)
	{
		handle_cd4(ms);
		chdir(ms->old_dir);
	}
	else
		actual_pwd(ms->new_dir, env, ms, 0);
	free(ms->new_dir);
	return (1);
}

int	handle_cd2(t_ms *ms, char **env, char **tab)
{
	int		i;
	char	cwd[1024];

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "..\0", 3) == 0)
		{
			ms->new_dir = going_back(ms->dir);
			if (!ms->new_dir)
				return (-1);
			chdir(ms->new_dir);
			actual_pwd(ms->new_dir, env, ms, 0);
			ms->dir = getcwd(cwd, 1024);
			free(ms->new_dir);
		}
		else if (tab[i] && ft_strncmp(tab[i], "..\0", 3) != 0)
		{
			handle_cd3(ms, env, tab, &i);
			ms->dir = getcwd(cwd, 1024);
		}
		i++;
	}
	return (1);
}

int	cd_home(t_ms *ms, char **env)
{
	char	*home;

	home = find_home(env);
	if (home)
	{
		chdir(home);
		actual_pwd(home, env, ms, 0);
	}
	else
		write(2, "minishell: cd: HOME not set\n", 29);
	free(home);
	return (1);
}

int	handle_cd(t_ms *ms, char **env, t_parser *parser)
{
	char	**tab;

	close_fd(parser, ms);
	if (ft_strncmp(parser->cmd[0], "cd\0", 2) == 0)
	{
		if (parser->cmd[1] && parser->cmd[2])
			return (ms->e_s = 1, cd_err(parser->cmd[1], \
			"too many arguments\n", 0), 1);
		if (!parser->cmd[1] || chdir(parser->cmd[1]) == -1)
		{
			ms->old_dir = ms->dir;
			tab = ft_split(parser->cmd[1], '/');
			if (!tab)
				cd_home(ms, env);
			else
				handle_cd2(ms, env, tab);
			ft_free_tab(tab);
		}
		else
			actual_pwd(ms->dir, env, ms, 0);
		ms->e_s = 0;
		return (1);
	}
	return (0);
}
