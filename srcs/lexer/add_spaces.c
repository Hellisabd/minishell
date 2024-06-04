/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:25:28 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/14 17:17:02 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add_spaces_brackets(char *our_line, t_ms *ms, int *j)
{
	if (ms->line[0] == '>' && ms->line[1] != '>')
	{
		our_line[1] = ' ';
		*j = 2;
	}
	if (ms->line[0] == '<' && ms->line[1] != '<')
	{
		our_line[1] = ' ';
		*j = 2;
	}
}

void	ft_add_spaces_and(char *our_line, t_ms *ms, int *i, int *j)
{
	our_line[*j] = ' ';
	(*j)++;
	our_line[*j] = ms->line[*i];
	(*j)++;
	(*i)++;
}

void	ft_add_spaces_before(char *our_line, int *j)
{
	our_line[*j] = ' ';
	(*j)++;
}

void	ft_add_spaces_after(char *our_line, t_ms *ms, int *i, int *j)
{
	our_line[*j + 1] = ' ';
	our_line[*j] = ms->line[*i];
	*j += 2;
	ms->boul = 1;
}

void	ft_add_spaces_everywhere(char *our_line, t_ms *ms, int *i, int *j)
{
	if (ms->line[*i] == '&' && !is_w_space(ms->line[*i - 1])
		&& ms->line[*i - 1] != '&' && !inside_thing(ms->line, *i, ms))
		ft_add_spaces_and(our_line, ms, i, j);
	if (ms->line[*i] == '|' && !is_w_space(ms->line[*i - 1])
		&& ms->line[*i - 1] != '|' && !inside_thing(ms->line, *i, ms))
		ft_add_spaces_before(our_line, j);
	if (ms->line[*i] == '|' && !is_w_space(ms->line[*i + 1])
		&& ms->line[*i + 1] != '|' && !inside_thing(ms->line, *i, ms))
		ft_add_spaces_after(our_line, ms, i, j);
	if (ms->line[*i] == '<' && !is_w_space(ms->line[*i - 1])
		&& ms->line[*i - 1] != '<' && !inside_thing(ms->line, *i, ms))
		ft_add_spaces_before(our_line, j);
	if (ms->line[*i] == '<' && !is_w_space(ms->line[*i + 1])
		&& ms->line[*i + 1] != '<' && !inside_thing(ms->line, *i, ms))
		ft_add_spaces_after(our_line, ms, i, j);
	if (ms->line[*i] == '>' && !is_w_space(ms->line[*i - 1])
		&& ms->line[*i - 1] != '>' && !inside_thing(ms->line, *i, ms))
		ft_add_spaces_before(our_line, j);
	if (ms->line[*i] == '>' && !is_w_space(ms->line[*i + 1])
		&& ms->line[*i + 1] != '>' && !inside_thing(ms->line, *i, ms))
		ft_add_spaces_after(our_line, ms, i, j);
}
