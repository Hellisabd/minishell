/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_gest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:05:20 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/28 16:07:58 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exit_err2(char *line, char *arg)
{
	line = ft_strjoin(line, "`");
	if (!line)
		return (NULL);
	line = ft_strjoin(line, arg);
	if (!line)
		return (NULL);
	line = ft_strjoin(line, "'");
	if (!line)
		return (NULL);
	return (line);
}

void	exit_err(char *cmd, char *arg, char *err, int b)
{
	char	*line;

	line = ft_strdup("minishell: ");
	if (!line)
		return ;
	line = ft_strjoin(line, cmd);
	if (!line)
		return ;
	if (b == 1)
	{
		line = exit_err2(line, arg);
		if (!line)
			return ;
		line = ft_strjoin(line, ": ");
		if (!line)
			return ;
	}
	line = ft_strjoin(line, err);
	if (!line)
		return ;
	ft_putstr_fd(line, 2);
	free(line);
}

void	cd_err(char *cmd, char *err, int b)
{
	char	*line;

	line = ft_strdup("minishell: cd: ");
	if (!line)
		return ;
	if (b == 1)
	{
		line = ft_strjoin(line, "`");
		if (!line)
			return ;
		line = ft_strjoin(line, cmd);
		if (!line)
			return ;
		line = ft_strjoin(line, "'");
		if (!line)
			return ;
	}
	line = ft_strjoin(line, ": ");
	if (!line)
		return ;
	line = ft_strjoin(line, err);
	if (!line)
		return ;
	ft_putstr_fd(line, 2);
	free(line);
}

void	h_d_err(char *infile, int n, char *line)
{
	line = ft_strdup("minishell: ");
	if (!line)
		return ;
	line = ft_strjoin(line, infile);
	if (!line)
		return ;
	if (n == 1)
	{
		line = ft_strjoin(line, ": No such file or directory\n");
		if (!line)
			return ;
	}
	if (n == 2)
	{
		line = ft_strjoin(line, ": Is a directory\n");
		if (!line)
			return ;
	}
	if (n == 3)
	{
		line = ft_strjoin(line, ": Permission denied\n");
		if (!line)
			return ;
	}
	free((ft_putstr_fd(line, 2), line));
}

void	command_err(char *cmd, t_ms *ms, t_parser *parser)
{
	char	*line;

	(void)parser;
	line = ft_strdup(cmd);
	if (!line)
		return ;
	line = ft_strjoin(line, ": command not found\n");
	if (!line)
		return ;
	ft_putstr_fd(line, 2);
	free(line);
	exit ((free(ms->path), ft_free_lexer(ms->lexer), \
	free(ms->tab_bool), ft_free_parser(ms->parser), \
	ms->e_s = 127, 127));
}
