/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:55:03 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/27 13:38:00 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	inside_thing(char *line, int size, t_ms *ms)
{
	int	i;

	i = -1;
	ms->quote = 0;
	ms->db_quote = 0;
	ms->par = 0;
	while (++i < size)
	{
		if (line[i] == '\'' && ms->db_quote % 2 == 0 && ms->par == 0)
			ms->quote++;
		if (line[i] == '"' && ms->quote % 2 == 0 && ms->par == 0)
			ms->db_quote++;
		if (line[i] == '(' && ms->quote % 2 == 0 && ms->db_quote % 2 == 0)
			ms->par++;
		if (line[i] == ')' && ms->par == 1)
			ms->par--;
	}
	if (ms->par != 0 && line[i] != ')')
		return (PAR);
	else if (ms->db_quote % 2 == 0 && ms->quote % 2 != 0 && line[i] != '\'')
		return (QUOTE);
	else if (ms->db_quote % 2 != 0 && line[i] != '"')
		return (DB_QUOTE);
	return (0);
}

void	ft_add_back_lexer(t_lexer **lexer, char *str)
{
	t_lexer	*tmp;
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		exit(EXIT_FAILURE);
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return ;
	new->next = NULL;
	new->err = 0;
	if (lexer == NULL || *lexer == NULL)
	{
		*lexer = new;
		return ;
	}
	tmp = *lexer;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	is_w_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

void	ft_add_space(char *our_line, t_ms *ms)
{
	int	i;
	int	j;

	our_line[0] = ms->line[0];
	i = 1;
	j = 1;
	if (!is_w_space(ms->line[1]))
		ft_add_spaces_brackets(our_line, ms, &j);
	while (ms->line[i])
	{
		ms->boul = 0;
		ft_add_spaces_everywhere(our_line, ms, &i, &j);
		if (ms->boul == 0)
		{
			our_line[j] = ms->line[i];
			j++;
		}
		i++;
	}
	our_line[j] = '\0';
}

void	printlist(t_lexer *node)
{
	while (node != NULL)
	{
		printf("%s | token: %d\n", node->str, node->token);
		node = node->next;
	}
}
