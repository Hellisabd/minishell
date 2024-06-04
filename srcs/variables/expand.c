/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:18:09 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/21 13:49:59 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expandables(char *cmd, char **env, t_ms *ms, t_expand *ex)
{
	if (cmd[ex->i + 1] == '$')
	{
		dollar_dollar(ms, ex);
		if (!ex->line)
			return ;
	}
	else if (cmd[ex->i + 1] == '?')
	{
		dollar_question(ex, ms);
		if (!ex->line)
			return ;
	}
	else if (cmd[ex->i + 1] == '\0' || is_w_space(cmd[ex->i + 1])
		|| (ex->i != 0 && cmd[ex->i - 1] == '"' && cmd[ex->i + 1] == '"'))
		expandables4(ex);
	else if (ft_isalnum(cmd[ex->i + 1]) == 0 || ft_isdigit(cmd[ex->i + 1]) != 0)
		ex->i = ex->i +2;
	else
	{
		dollar_stuff(env, cmd, ex);
		if (!ex->line)
			return ;
	}
	ex->j = ex->i;
}

void	expandables2(char *cmd, char **env, t_ms *ms, t_expand *ex)
{
	ex->size = 0;
	ex->tmp = ft_strndup(cmd, ex->i);
	if (!ex->tmp)
		return (free(ex->line));
	ex->line = ft_strjoin(ex->line, ex->tmp + ex->j);
	if (!ex->line && ex->i != 0)
		return (free(ex->tmp));
	free(ex->tmp);
	expandables(cmd, env, ms, ex);
}

void	expandables3(char *cmd, t_expand *ex)
{
	if (ex->stock != 0)
	{
		ex->tmp = ft_strdup(cmd);
		if (!ex->tmp)
			return (free(ex->line));
		ex->line = ft_strjoin(ex->line, ex->tmp + (ex->i - ex->stock));
		if (!ex->line)
			return (free(ex->tmp));
		free(ex->tmp);
	}
}

char	*expand(char *cmd, char **env, t_ms *ms)
{
	t_expand	ex;

	ex.line = NULL;
	ex.i = 0;
	ex.j = 0;
	ex.stock = 0;
	while (cmd[ex.i])
	{
		if (cmd[ex.i] == '$' && inside_thing(cmd, ex.i, ms) != QUOTE)
		{
			expandables2(cmd, env, ms, &ex);
			if (!ex.line)
				return (NULL);
			ex.stock = 0;
		}
		else
			lol((ex.i++, ex.stock++, 0));
	}
	expandables3(cmd, &ex);
	if (!ex.line)
		return (NULL);
	cmd = ft_strdup(ex.line);
	if (!cmd)
		return (NULL);
	return (free(ex.line), cmd);
}

char	*verif_dollar(char *str, char **env, t_ms *ms)
{
	char	*new_str;
	int		i;

	i = 0;
	if (ft_strchr(str, '$') != 0)
	{
		new_str = expand(str, env, ms);
		return (new_str);
	}
	new_str = ft_strdup(str);
	return (new_str);
}
