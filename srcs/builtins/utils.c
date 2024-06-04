/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:26:18 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/29 12:07:54 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	size_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	parse_export(char *s)
{
	int	i;

	i = 0 ;
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '=')
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (2);
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (0);
		i++;
	}
	if (ft_strchr(s, '=') == 0)
		return (3);
	return (1);
}

int	same_char(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] < str2[i])
		return (2);
	return (1);
}

int	replace(char **cmd, char **env, int i, t_ms *ms)
{
	char	*line;
	int		size;

	if (ft_strchr(cmd[i], '=') != 0)
	{
		line = ft_strdup(cmd[i]);
		if (!line)
			return (0);
		size = search_and_replace(cmd[i], env);
		if (ms->tab_bool[size] == true)
			free(env[size]);
		else
			ms->tab_bool[size] = true;
		env[size] = ft_strdup(line);
		if (!env[size])
			return (0);
		free(line);
		return (1);
	}
	return (-1);
}

int	new_var(char **cmd, char **env, int i, t_ms *ms)
{
	char	*line;
	int		size;
	int		h;
	int		j;

	j = 0;
	h = 0;
	line = malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1));
	while (cmd[i][h])
	{
		if (cmd[i][h] == '+' && cmd[i][h + 1] == '=')
			h++;
		line[j++] = cmd[i][h++];
	}
	line[j] = '\0';
	if (!line)
		return (0);
	size = size_env(env);
	env[size] = ft_strdup(line);
	env[size + 1] = NULL;
	ms->tab_bool = new_tabool(env, ms->tab_bool);
	free(line);
	if (!env[size])
		return (0);
	return (1);
}
