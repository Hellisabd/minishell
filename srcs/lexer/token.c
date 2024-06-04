/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:59:45 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/28 17:02:43 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	token1(t_lexer **tmp)
{
	if ((*tmp)->str[0] == '<' && (*tmp)->str[1] == '<' && !(*tmp)->str[2])
	{
		(*tmp)->token = HEREDOC;
		(*tmp)->next->token = LIMITER;
		return (((*tmp) = (*tmp)->next), false);
	}
	else if ((*tmp)->str[0] == '<' && !(*tmp)->str[1])
	{
		(*tmp)->token = SINGLE_LEFT;
		(*tmp)->next->token = INFILE;
		return (((*tmp) = (*tmp)->next), false);
	}
	else if ((*tmp)->str[0] == '>' && (*tmp)->str[1] == '>')
	{
		(*tmp)->token = DOUBLE_RIGHT;
		(*tmp)->next->token = OUTFILE2;
		return (((*tmp) = (*tmp)->next), false);
	}
	else if ((*tmp)->str[0] == '>')
	{
		(*tmp)->token = SINGLE_RIGHT;
		(*tmp)->next->token = OUTFILE;
		return (((*tmp) = (*tmp)->next), false);
	}
	return (true);
}

void	token2(t_lexer **tmp, int *count)
{
	if ((*tmp)->str[0] == '|' && (*tmp)->str[1] == '|')
	{
		(*tmp)->token = OR;
		*count = 0;
	}
	else if ((*tmp)->str[0] == '|')
	{
		(*tmp)->token = PIPE;
		*count = 0;
	}
	else if ((*tmp)->str[0] == '&' && (*tmp)->str[1] == '&')
	{
		(*tmp)->token = AND;
		*count = 0;
	}
	else if (*count == 0 && (*tmp)->str[0] != '\0')
	{
		(*tmp)->token = CMD;
		*count = 1;
	}
	else if ((*tmp)->str[0] != '\0')
		(*tmp)->token = WORD;
	else
		(*tmp)->token = BLANK;
}

int	get_token(t_lexer **lexer, t_ms *ms)
{
	int		count;
	t_lexer	*tmp;

	count = 0;
	tmp = *lexer;
	while (tmp)
	{
		if (!tmp->next && (!tmp->str[1]
				|| !tmp->str[2]) && (tmp->str[0] == '<' || tmp->str[0] == '>'
				|| tmp->str[0] == '|' || tmp->str[0] == '&'))
		{
			tmp->token = -1;
			return (ft_putstr_fd \
			("minishell: syntax error near unexpected token `newline'\n"\
			, 2), -1);
		}
		if (token1(&tmp))
			token2(&tmp, &count);
		if (tmp->err == 1)
			return (tmp->err = 0, ms->e_s = 1, -1);
		tmp = tmp->next;
	}
	if (-1 == pipe_err(*lexer))
		return (-1);
	return (0);
}
