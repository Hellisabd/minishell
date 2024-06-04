/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:30:42 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/28 13:43:10 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**find_path(char **env)
{
	char	**tmp;
	int		i;

	i = -1;
	while (*env && 0 != ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (NULL);
	tmp = ft_split(*env + 5, ':');
	if (!tmp)
		return (NULL);
	while (tmp[++i])
	{
		tmp[i] = ft_strjoin(tmp[i], "/");
		if (!tmp[i])
			return (ft_free_tab(tmp), NULL);
	}
	return (tmp);
}

void	parsing3(t_lexer **start, t_lexer **end, t_parser **tmp, t_ms *ms)
{
	while ((*start) != (*end))
	{
		if (((*start)->token == CMD
				|| (*start)->token == WORD))
		{
			(*tmp)->cmd[ms->i] = ft_strdup((*start)->str);
			ms->i++;
		}
		if ((*start)->token == DOUBLE_RIGHT)
			file_gest((*start)->next, tmp);
		if ((*start)->token == LIMITER)
		{
			file_gest(*start, tmp);
		}
		if ((*start)->token == INFILE)
			file_gest(*start, tmp);
		if ((*start)->token == OUTFILE)
		{
			file_gest(*start, tmp);
		}
		if ((*start)->token == FILE_DOOMED)
			(*tmp)->file_err = 1;
		(*start) = (*start)->next;
	}
}

void	parsing2(t_lexer **end, t_lexer **start, t_ms *ms, t_parser *tmp)
{
	while (*end)
	{
		*start = *end;
		while (*end && (*end)->token != OR && (*end)->token != AND
			&& (*end)->token != PIPE)
		{
			if (((*end)->token == CMD || (*end)->token == WORD))
				ms->i++;
			(*end) = (*end)->next;
		}
		tmp->cmd = malloc(sizeof(char *) * (ms->i + 1));
		if (!tmp->cmd)
			return ;
		ms->i = 0;
		parsing3(start, end, &tmp, ms);
		tmp->cmd[ms->i] = NULL;
		if ((*end))
			(*end) = (*end)->next;
		tmp = tmp->next;
	}
}

void	parsing(t_ms *ms)
{
	t_lexer		*end;
	t_lexer		*start;

	ms->i = 1;
	end = *ms->lexer;
	start = NULL;
	ms->parser = NULL;
	while (end)
	{
		if (end && (end->token == OR || end->token == AND
				|| end->token == PIPE))
			ms->i++;
		if (end->token == -1)
			return ;
		end = end->next;
	}
	while (ms->i > 0)
	{
		ft_add_back_parser(&ms->parser, NULL);
		ms->i--;
	}
	printparser(ms->parser);
	end = (*ms->lexer);
	parsing2(&end, &start, ms, ms->parser);
	ms->i = 0;
}
