/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:56:18 by bgrosjea          #+#    #+#             */
/*   Updated: 2025/05/16 13:35:31 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	calc_size1(int *size, t_ms *ms, int i)
{
	if (ms->line[i] == '&' && !is_w_space(ms->line[i - 1])
		&& ms->line[i - 1] != '&' && !inside_thing(ms->line, i, ms))
		(*size)++;
	else if (ms->line[i] == '&' && !is_w_space(ms->line[i + 1])
		&& ms->line[i + 1] != '&' && !inside_thing(ms->line, i, ms))
		(*size)++;
	if (ms->line[i] == '|' && !is_w_space(ms->line[i - 1])
		&& ms->line[i - 1] != '|' && ms->line[i + 1] != '|'
		&& !is_w_space(ms->line[i + 1]) && !inside_thing(ms->line, i, ms))
		(*size) = (*size) + 2;
	else if (ms->line[i] == '|' && !is_w_space(ms->line[i - 1])
		&& ms->line[i - 1] != '|' && !inside_thing(ms->line, i, ms))
		(*size)++;
	else if (ms->line[i] == '|' && !is_w_space(ms->line[i + 1])
		&& ms->line[i + 1] != '|' && !inside_thing(ms->line, i, ms))
		(*size)++;
}

void	calc_size2(int *size, t_ms *ms, int i)
{
	if (ms->line[i] == '<' && !is_w_space(ms->line[i - 1])
		&& ms->line[i - 1] != '<' && ms->line[i + 1] != '<'
		&& !is_w_space(ms->line[i + 1]) && !inside_thing(ms->line, i, ms))
		(*size) = (*size) + 2;
	else if (ms->line[i] == '<' && !is_w_space(ms->line[i - 1])
		&& ms->line[i - 1] != '<' && !inside_thing(ms->line, i, ms))
		(*size)++;
	else if (ms->line[i] == '<' && !is_w_space(ms->line[i + 1])
		&& ms->line[i + 1] != '<' && !inside_thing(ms->line, i, ms))
		(*size)++;
	if (ms->line[i] == '>' && !is_w_space(ms->line[i - 1])
		&& ms->line[i - 1] != '>' && ms->line[i + 1] != '>'
		&& !is_w_space(ms->line[i + 1]) && !inside_thing(ms->line, i, ms))
		(*size) = (*size) + 2;
	else if (ms->line[i] == '>' && !is_w_space(ms->line[i - 1])
		&& ms->line[i - 1] != '>' && !inside_thing(ms->line, i, ms))
		(*size)++;
	else if (ms->line[i] == '>' && !is_w_space(ms->line[i + 1])
		&& ms->line[i + 1] != '>' && !inside_thing(ms->line, i, ms))
		(*size)++;
}

char	*init_lexer(t_ms *ms)
{
	int		i;
	int		size;
	char	*our_line;

	i = 1;
	size = 0;
	while (ms->line && ms->line[i])
	{
		calc_size1(&size, ms, i);
		calc_size2(&size, ms, i);
		i++;
	}
	our_line = malloc(sizeof(char) * (i + size + 2));
	if (!our_line)
		return (free(ms->line), NULL);
	ft_add_space(our_line, ms);
	free(ms->line);
	return (our_line);
}

void	lexer3(t_ms *ms, t_lexer *tmp, char **env, char *str)
{
	while (tmp)
	{
		str = verif_dollar(tmp->str, env, ms);
		free(tmp->str);
		tmp->str = remove_quote_str(str, ms);
		free(str);
		tmp = tmp->next;
	}
	ms->new_dir = NULL;
}

t_lexer	**lexer(t_ms *ms, char **env)
{
	char	**tab;
	int		size;
	t_lexer	**lexer;
	int		i;

	i = -1;
	ms->b = 0;
	lexer = malloc(sizeof(t_lexer *));
	if (!lexer)
		return (NULL);
	*lexer = NULL;
	ms->line = init_lexer(ms);
	tab = ft_split_lexer(ms->line);
	size = size_tab(tab);
	while (size > ++i)
	{
		ms->b = 0;
		ft_add_back_lexer(lexer, tab[i]);
	}
	if (get_token((ft_free_tab(tab), lexer), ms) == -1)
		return (ft_free_lexer(lexer), lexer = NULL, NULL);
	if (!(*lexer))
		return (free(lexer), NULL);
	lexer3(ms, *lexer, env, NULL);
	return (lexer);
}
