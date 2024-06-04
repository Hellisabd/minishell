/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:24:53 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 12:53:25 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	plus_equal2(t_ms *sup, char **env, int i, t_ms *ms)
{
	char	*tmp;

	tmp = ft_strstartdup(sup->tmp, i + 2);
	if (!tmp)
		return (0);
	if (ms->tab_bool[sup->n] == true)
		env[sup->n] = ft_strjoin(env[sup->n], tmp);
	else
	{
		env[sup->n] = ft_strjoin_const(env[sup->n], tmp);
		ms->tab_bool[sup->n] = true;
	}
	if (!env[sup->n])
		return (free(tmp), 0);
	return (free(tmp), 1);
}

int	plus_equal(char *cmd, char **env, int i, t_ms *ms)
{
	t_ms	sup;

	sup.n = -1;
	while (cmd[i] && cmd[i] != '+')
		i++;
	while (env[++sup.n])
	{
		sup.b = 0;
		while (env[sup.n][sup.b] && env[sup.n][sup.b] != '=')
			sup.b++;
		if (ft_strncmp(cmd, env[sup.n], i) == 0
			&& ft_strncmp(cmd, env[sup.n], sup.b) == 0)
		{
			sup.tmp = cmd;
			if (plus_equal2(&sup, env, i, ms) == 1)
				return (1);
		}
	}
	return (0);
}

bool	*new_tabool(char **env, bool *tab)
{
	int		i;
	bool	*new_tab;

	i = 0;
	new_tab = malloc(sizeof(bool) * (size_env(env) + 1));
	while (i < size_env(env) - 1)
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = true;
	free(tab);
	return (new_tab);
}

int	parse_export2(char **cmd, char **env, int i, t_ms *ms)
{
	int	size;

	size = size_env(env);
	if (parse_export(cmd[i]) == 0)
		return (-1);
	else if (parse_export(cmd[i]) == 1)
	{
		if (new_var(cmd, env, i, ms) == 0)
			return (-1);
	}
	else if (parse_export(cmd[i]) == 3)
	{
		env[size] = ft_strdup(cmd[i]);
		env[size + 1] = NULL;
		ms->tab_bool = new_tabool(env, ms->tab_bool);
		return (1);
	}
	else if (parse_export(cmd[i]) == 2)
		if (plus_equal(cmd[i], env, 0, ms) == 0)
			if (new_var(cmd, env, i, ms) == 0)
				return (-1);
	return (1);
}

int	handle_export(char **env, int i, t_parser *parser, t_ms *ms)
{
	if (ft_strncmp(parser->cmd[0], "export\0", 7) == 0)
	{
		if (!parser->cmd[1])
			if (print_export(env) == 0)
				return (1);
		if (parser->cmd[1][0] == '=')
			return (exit_err("export: ", parser->cmd[1], \
					"not a valid identifier\n", 1), ms->e_s = 1, 1);
		while (parser->cmd[++i])
		{
			if (search_and_replace(parser->cmd[i], env) != -1)
			{
				if (replace(parser->cmd, env, i, ms) == 0)
					return (-1);
			}
			else if (parse_export2(parser->cmd, env, i, ms) == -1)
				return (exit_err("export: ", parser->cmd[i], \
					"not a valid identifier\n", 1), ms->e_s = 1, 1);
		}
		ms->e_s = 0;
		return (1);
	}
	return (0);
}
