/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:14:49 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/27 13:48:07 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

bool	inside_thing_split(char *line, int size)
{
	int	i;
	int	quote;
	int	db_quote;
	int	par;

	i = -1;
	quote = 0;
	db_quote = 0;
	par = 0;
	while (++i < size)
	{
		if (line[i] == '\'' && db_quote % 2 == 0 && par == 0)
			quote++;
		if (line[i] == '"' && quote % 2 == 0 && par == 0)
			db_quote++;
		if (line[i] == '(' && quote % 2 == 0 && db_quote % 2 == 0)
			par++;
		if (line[i] == ')' && par == 1)
			par--;
	}
	if (quote % 2 == 0 && db_quote % 2 == 0 && par % 2 == 0)
		return (true);
	return (false);
}

static	int	ft_splitsplit(char *s, char c, t_m *var, char **res)
{
	if (s[var->i] != c && var->h < 0)
		var->h = var->i;
	else if (((s[var->i] == c || var->i == ft_strlen(s)) && var->h >= 0
			&& inside_thing_split(s, var->i)) || s[var->i] == '\0')
	{
		res[var->j] = fill_dest(s, var);
		if (!res[var->j++] && free_split(res, var->j - 1) == 0)
			return (0);
		var->h = -1;
	}
	var->i++;
	return (1);
}

char	**ft_split_lexer(char *s, char c)
{
	char	**res;
	t_m		var;

	if (!s)
		return (NULL);
	var.j = 0;
	var.h = -1;
	var.i = 0;
	res = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (var.i <= ft_strlen(s))
	{
		if (ft_splitsplit(s, c, &var, res) == 0)
			return (NULL);
	}
	res[var.j] = 0;
	free(s);
	return (res);
}
