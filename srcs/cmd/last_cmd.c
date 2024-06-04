/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:06:35 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/30 12:55:03 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_wait(void)
{
	passive_sig();
}

void	last_cmd_dup_gest(t_parser *parser, t_ms *ms)
{
	if (ms->fd && parser->fdin == 0 && parser->fd[0] == -1)
	{
		if (dup2(ms->fd[ms->i - 1][0], 0) < 0)
			exit ((close_fd(ms->parser, ms), \
			ft_free_tab(ms->path), perror("Error1b"), 1));
	}
	else if (parser->fd[0] != -1 && check_last_file(parser->file) == LIMITER)
	{
		if (0 > dup2((parser->fd[0]), 0))
			exit ((ft_free_tab(ms->path), close_fd(parser, ms), \
			perror("ERROR"), 1));
	}
	else
	{
		if (dup2(parser->fdin, 0) < 0)
			exit ((close_fd(ms->parser, ms), \
			ft_free_tab(ms->path), perror("Error2b"), 1));
	}
	if (parser->fdout != 1)
	{
		if (dup2(parser->fdout, 1) < 0)
			exit ((close_fd(ms->parser, ms), \
				ft_free_tab(ms->path), perror("Error3b"), 1));
	}
}

void	last_cmd(t_parser *parser, t_ms *ms, char **env)
{
	open_files(ms, parser);
	if (parser->cmd && *parser->cmd)
	{
		last_cmd_dup_gest(parser, ms);
		if (handle_echo(parser->cmd, parser, ms) == 0
			&& handle_pwd(parser->cmd, ms->parser, ms) == 0
			&& handle_env(parser, env, ms->parser, ms) == 0
			&& handle_export(env, 0, parser, ms) == 0
			&& handle_unset(parser->cmd, env, ms) == 0
			&& handle_cd(ms, env, parser) == 0
			&& handle_exit(parser->cmd, ms, env, parser) == 0)
			exec_cmd(ms, parser, env);
		else
		{
			close_fd(ms->parser, ms);
			exit ((ft_free_parser(ms->parser), \
			free(ms->tab_bool), free(ms->prompt), ft_free_lexer(ms->lexer), \
			ft_free_tab(ms->path), 0));
		}
	}	
	exit ((close_fd(ms->parser, ms), ft_free_parser(ms->parser), \
	free(ms->tab_bool), free(ms->prompt), ft_free_lexer(ms->lexer), \
	ft_free_tab(ms->path), 0));
}

void	last_cmd_gest2(t_ms *ms, t_parser *tmp, char **env)
{
	if (tmp->cmd && tmp->cmd[0] && tmp->cmd[0][0] == '.' && tmp->cmd[0][1] \
	== '/' && tmp->cmd && *tmp->cmd && access(tmp->cmd[0], F_OK) == 0)
	{
		if (access(tmp->cmd[0], X_OK) == 0)
			sig_wait();
	}
	last_cmd(tmp, ms, env);
	close_fd(ms->parser, ms);
}

void	last_cmd_gest(t_ms *ms, t_parser *tmp, t_parser *parser, char **env)
{
	tmp->pid = fork();
	if (tmp->pid == 0)
	{
		close (ms->history);
		last_cmd_gest2(ms, tmp, env);
	}
	if (tmp->cmd && tmp->cmd[0] && tmp->cmd[0][0] == '.' && tmp->cmd[0][1] \
	== '/' && tmp->cmd && *tmp->cmd && access(tmp->cmd[0], F_OK) == 0)
		if (access(tmp->cmd[0], X_OK) == 0)
			sig_wait();
	while (parser)
	{
		if (parser->fdin != 0)
			close (parser->fdin);
		parser = parser->next;
	}
	if (ms->nb_cmd > 1)
	{
		close(ms->fd[ms->i - 1][1]);
		ms->fd[ms->i - 1][1] = -1;
		close(ms->fd[ms->i - 1][0]);
		ms->fd[ms->i - 1][0] = -1;
	}
}
