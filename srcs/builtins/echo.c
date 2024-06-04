/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:04:55 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 12:52:34 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_n(char **cmd, int *i, char	**s)
{
	int		j;

	while (cmd[(*i)])
	{
		j = 1;
		if (ft_strncmp(cmd[(*i)], "-n", 2) == 0)
		{
			while (cmd[*i][j] == 'n')
				j++;
			if (cmd[*i][j] != '\0')
				return (*s = ft_strdup(cmd[((*i)++)]), 0);
			(*i)++;
		}
		else
		{
			*s = ft_strdup(cmd[(*i)]);
			if (!*s)
				return (-1);
			(*i)++;
			break ;
		}
	}
	return (0);
}

int	join_echo(char **cmd, char **s, int i)
{
	char	*tmp1;
	char	*tmp2;

	*s = ft_strjoin(*s, " ");
	if (!(*s))
		return (0);
	tmp1 = ft_strdup(cmd[i]);
	if (!tmp1)
		return (free(*s), 0);
	tmp2 = ft_strjoin(*s, tmp1);
	if (!tmp2)
		return (free(*s), free(tmp1), 0);
	free(tmp1);
	*s = tmp2;
	return (1);
}

void	handle_n(char **cmd, int *i, char **s)
{
	if (!cmd[2])
		return ;
	skip_n(cmd, i, s);
	if (!s)
		return ;
	while (cmd[*i])
	{
		if (join_echo(cmd, s, *i) == 1)
			(*i)++;
	}
	if (*s)
	{
		printf("%s", *s);
		free (*s);
	}
}

int	handle_echo2(char **cmd, t_parser *parser, t_ms *ms, char *s)
{
	int	i;

	i = 2;
	if (parser->file && ms->i == 0 && ms->nb_cmd == 1)
	{
		open_files(ms, parser);
		first_command_dup_gest(ms, parser);
	}
	if (!cmd[1])
		printf("\n");
	else if (ft_strncmp(cmd[1], "-n", 2) == 0)
		handle_n(cmd, &i, &s);
	else
		if (handle_echo3(cmd, s, i) == 1)
			return (1);
	close_fd(parser, ms);
	if (parser->file && ms->i == 0 && ms->nb_cmd == 1)
	{
		close(ms->history);
		exit ((close_fd(ms->parser, ms), ft_free_parser(ms->parser), \
		free(ms->tab_bool), free(ms->prompt), ft_free_lexer(ms->lexer), \
		ft_free_tab(ms->path), 0));
	}
	return (0);
}

int	handle_echo(char **cmd, t_parser *parser, t_ms *ms)
{
	int		status;

	status = 0;
	if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
	{
		if (parser->file && ms->i == 0 && ms->nb_cmd == 1)
			parser->pid = fork();
		if (parser->pid == 0 || (!parser->file && ms->i != 0))
		{
			if (handle_echo2(cmd, parser, ms, NULL) == 1)
				return (1);
		}
		else if (ms->nb_cmd == 1)
		{
			close_fd(parser, ms);
			waitpid(parser->pid, &status, 0);
			exit_end(status, ms);
		}
		ms->e_s = 0;
		return (1);
	}
	return (0);
}
