/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_gest2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:24 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/14 17:18:18 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	in_gest(char **cmd, int i, char c, t_parser *parser)
{
	if (c == '\'')
	{
		cmd[i] = ft_strtrim(cmd[i], "'");
		if (!cmd[i])
			return (-1);
		parser->tab[i] = 1;
	}
	else
	{
		cmd[i] = ft_strtrim(cmd[i], "\"");
		if (!cmd[i])
			return (-1);
		parser->tab[i] = 0;
	}
	return (1);
}

char	*in_gest_str(char *cmd, char c, t_ms *ms)
{
	char	*tmp;
	char	*tmp1;

	tmp1 = ft_strdup(cmd);
	if (c == '\'')
	{
		tmp = ft_strtrim(tmp1, "'");
		ms->b = 1;
		if (!tmp)
			return (tmp);
	}
	else
	{
		tmp = ft_strtrim(tmp1, "\"");
		if (!tmp)
			return (tmp);
	}
	return (tmp);
}
