/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:33:24 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/28 09:58:25 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_parser(t_parser *parser)
{
	t_parser	*tmp;
	t_file		*tmp1;

	while (parser)
	{
		tmp = parser;
		parser = parser->next;
		if (tmp)
		{
			ft_free_tab(tmp->cmd);
			free(tmp->tab);
			while (tmp->file)
			{
				tmp1 = tmp->file;
				if (tmp)
					tmp->file = tmp->file->next;
				free(tmp1->filename);
				free(tmp1);
			}
			tmp->cmd = NULL;
			free(tmp);
		}
	}
	free(parser);
}

void	free_file(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file;
		file = file->next;
		free(tmp->filename);
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;

	while (lexer && *lexer)
	{
		tmp = *lexer;
		*lexer = (*lexer)->next;
		if (tmp && tmp->str)
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		free(tmp);
	}
	free(lexer);
	lexer = NULL;
}

void	free_exlist(t_export *ex)
{
	t_export	*tmp;

	while (ex)
	{
		tmp = ex;
		ex = ex->next;
		free(tmp->var);
		free(tmp);
	}
}

void	ft_free_env(t_ms *ms, char **env)
{
	int	i;

	i = 0;
	while (i < size_env(env))
	{
		if (ms->tab_bool[i] == true)
			free(env[i]);
		i++;
	}
}
