/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_gest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:02:34 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/29 13:35:49 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_all(char *cmd, t_ms *ms)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	while (cmd && cmd[i])
	{
		while (cmd[i] && ((cmd[i] == '\'' || cmd[i] == '"')
				&& !inside_thing(cmd, i, ms)))
			i++;
		if (cmd[i])
		{
			tmp[j] = cmd[i];
			j++;
			i++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

int	in_quote(char *cmd)
{
	int		i;
	int		j;
	char	c;

	j = 1;
	c = '\0';
	i = ft_strlen(cmd) - 1;
	if (cmd[0] == '"' && cmd[i] == '"')
		c = '"';
	if (cmd[0] == '\'' && cmd[i] == '\'')
		c = '\'';
	while (j < i)
	{
		if (cmd[j] == c)
			return (0);
		j++;
	}
	if (cmd[0] == '"' && cmd[i] == '"')
		return (DB_QUOTE);
	if (cmd[0] == '\'' && cmd[i] == '\'')
		return (QUOTE);
	return (0);
}

bool	has_quote(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

char	**remove_quote(char **cmd, t_parser *parser, t_ms *ms)
{
	int	i;

	parser->tab = malloc((i = 0, sizeof(int) * size_tab(cmd)));
	while (cmd && cmd[i])
	{
		if (has_quote(cmd[i]))
		{
			if (in_quote(cmd[i]) == QUOTE)
			{
				if (in_gest(cmd, i, '\'', parser) == -1)
					return (NULL);
			}
			else if (in_quote(cmd[i]) == DB_QUOTE)
			{
				if (in_gest(cmd, i, '"', parser) == -1)
					return (NULL);
			}
			else
				cmd[i] = remove_all(cmd[i], ms);
		}
		else
			parser->tab[i] = 0;
		i++;
	}
	return (cmd);
}

char	*remove_quote_str(char *str, t_ms *ms)
{
	if (str && has_quote(str))
	{
		if (in_quote(str) == QUOTE)
		{
			ms->tmp1 = in_gest_str(str, '\'', ms);
			if (!str)
				return (NULL);
		}
		else if (in_quote(str) == DB_QUOTE)
		{
			ms->tmp1 = in_gest_str(str, '"', ms);
			if (!str)
				return (NULL);
		}
		else
			ms->tmp1 = remove_all(str, ms);
	}
	else
		ms->tmp1 = ft_strdup(str);
	ms->tmp = ft_strdup(ms->tmp1);
	return (free(ms->tmp1), ms->tmp);
}
