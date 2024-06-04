/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:25:52 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/30 13:34:19 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_trash(char *tmp, char *limiter)
{
	tmp = get_next_line(0);
	if (g_e_s == 130)
		return (free(tmp), 130);
	if (!tmp)
		return ((ft_putstr_fd \
		("mini: warning: here-document delimited by end-of-file\n", 2), \
		free(tmp), 130));
	if (0 == ft_strncmp(limiter, tmp, ft_strlen(limiter)))
		if (tmp[ft_strlen(limiter)] == '\n')
			return ((free(tmp), 130));
	free(tmp);
	return (0);
}

void	trash_here_doc(t_ms *ms, char *limiter, char *tmp)
{
	while (1)
	{
		if (g_e_s == 130)
			exit ((close(ms->history), exit_child(ms), free(tmp), 130));
		if (exec_trash(tmp, limiter) == -1)
			break ;
	}
}

void	printparser(t_parser *node)
{
	int		i;
	t_file	*tmp;

	while (node != NULL)
	{
		i = 0;
		while (node->cmd && node->cmd[i])
		{
			printf("cmd : ");
			printf("%s\n", node->cmd[i]);
			i++;
		}
		tmp = node->file;
		while (tmp)
		{
			printf("filename : %s | \
			filetype : %d\n", tmp->filename, tmp->type);
			tmp = tmp->next;
		}
		node = node->next;
	}
}

void	ft_add_back_parser(t_parser **parser, t_parser *new)
{
	t_parser	*tmp;

	new = malloc((sizeof(t_parser)));
	if (!new)
		exit(EXIT_FAILURE);
	new->next = NULL;
	new->cmd = NULL;
	new->open_out = 0;
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->fdin = 0;
	new->fdout = 1;
	new->tab = NULL;
	new->file = NULL;
	new->file_err = 0;
	new->pid = 0;
	if (parser == NULL || *parser == NULL)
	{
		*parser = new;
		return ;
	}
	tmp = *parser;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
