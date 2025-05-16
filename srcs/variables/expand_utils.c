/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:13:45 by amirloup          #+#    #+#             */
/*   Updated: 2025/05/16 13:37:12 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	do_nothing(int i)
{
	(void)i;
}

int	size_expand(char *cmd, int n)
{
	int	i;

	i = n + 1;
	while (cmd[i] && ft_isalnum(cmd[i]) == 1)
		i++;
	return (i - n - 1);
}

int	search_env(char *cmd, char **env, int size)
{
	int	j;

	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], cmd, size) == 0 && env[j][size] == '=')
			return (j);
		j++;
	}
	return (-1);
}

void	dollar_dollar(t_ms *ms, t_expand *ex)
{
	char	*pid;

	(void)ms;
	pid = ft_itoa(ft_getppid(STATUS_FILE));
	if (!pid)
		return ;
	ex->line = ft_strjoin(ex->line, pid);
	free(pid);
	if (!ex->line)
		return ;
	ex->i = ex->i + 2;
}

void	dollar_stuff(char **env, char *cmd, t_expand *ex)
{
	char	*tmp;
	int		env_pos;

	ex->size = size_expand(cmd, ex->i);
	tmp = ft_strndup(cmd + (ex->i + 1), ex->size);
	if (!tmp)
		return ;
	env_pos = search_env(tmp, env, ex->size);
	free(tmp);
	if (env_pos == -1)
	{
		tmp = malloc(1);
		tmp[0] = '\0';
		ex->line = ft_strjoin(ex->line, tmp);
		free(tmp);
		ex->i += ex->size + 1;
		return ;
	}
	else
	{
		ex->line = ft_strjoin(ex->line, (env[env_pos] + ex->size + 1));
		if (!ex->line)
			return ;
	}
	ex->i += ex->size + 1;
}
