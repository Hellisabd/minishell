/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:21:50 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/29 13:05:28 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_home(char **env)
{
	char	*home;

	home = NULL;
	while (*env && 0 != ft_strncmp(*env, "HOME=", 5))
		env++;
	if (*env)
		home = ft_strdup(*env + 5);
	if (!home)
		return (NULL);
	return (home);
}

int	search_and_replace(char *cmd, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	while (env[j])
	{
		if (ft_strncmp(env[j], cmd, i) == 0)
			return (j);
		j++;
	}
	return (-1);
}

char	*going_back(char *dir)
{
	char	*new_dir;
	int		i;
	int		j;

	i = ft_strlen(dir);
	j = 0;
	while (dir[i] != '/')
		i--;
	new_dir = (char *)malloc (sizeof(char) * (i + 1));
	if (!new_dir)
		return (NULL);
	while (dir[j] && j != i)
	{
		new_dir[j] = dir[j];
		j++;
	}
	new_dir[j] = '\0';
	return (new_dir);
}

char	*going_forward(char *dir, char *cmd)
{
	char	*new_dir;

	new_dir = ft_strdup(dir);
	if (!new_dir)
		return (NULL);
	new_dir = ft_strjoin(new_dir, "/");
	if (!new_dir)
		return (NULL);
	new_dir = ft_strjoin(new_dir, cmd);
	if (!new_dir)
		return (NULL);
	return (new_dir);
}

int	handle_echo3(char **cmd, char *s, int i)
{
	i = 1;
	if (!cmd[1])
		return (1);
	while (cmd[i])
	{
		if (join_echo(cmd, &s, i) == 1)
			i++;
	}
	printf("%s\n", s + 1);
	free(s);
	return (0);
}
