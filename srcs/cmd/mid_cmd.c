/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:17:48 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 17:39:08 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_cmd(t_ms *ms, t_parser *parser, char **env, int blank)
{
	if (!parser->cmd || !*parser->cmd || !parser->cmd[blank])
		exit ((exit_child(ms), 0));
	if (ft_strncmp(parser->cmd[0], "/", 1)
		|| ft_strncmp(parser->cmd[0], "./", 1)
		|| ft_strncmp(parser->cmd[0], "../", 1))
		if (access(parser->cmd[0], F_OK) == 0)
			if (access(parser->cmd[0], X_OK) == 0)
				if (execve(parser->cmd[0], parser->cmd, env) == -1)
					is_dir(ms, parser->cmd[0]);
}

void	dup_gest(t_parser *tmp, t_ms *ms)
{
	int	fd;

	if (ms->fd && tmp->fdin == 0 && tmp->fd[0] == -1)
		fd = ms->fd[ms->i - 1][0];
	else if (tmp->fd[0] != -1 && check_last_file(tmp->file) == LIMITER)
		fd = tmp->fd[0];
	else
		fd = tmp->fdin;
	if (0 > dup2(fd, 0))
		exit ((ft_free_tab(ms->path), \
		close_fd(ms->parser, ms), perror("ERROR"), 1));
	if (tmp->fdout != 1)
		fd = tmp->fdout;
	else
		fd = ms->fd[ms->i][1];
	if (0 > dup2(fd, 1))
		exit ((close_fd(ms->parser, ms), \
		ft_free_tab(ms->path), perror("Error3a"), 1));
}

void	all_cmd_gest_2(t_ms *ms, t_parser *tmp, char **env)
{
	if (tmp->cmd && *tmp->cmd && tmp->cmd[0][0] == '.'
		&& tmp->cmd[0][1] == '/' && access(tmp->cmd[0], F_OK) == 0)
	{
		if (access(tmp->cmd[0], X_OK) == 0)
			passive_sig();
	}
	open_files(ms, tmp);
	dup_gest(tmp, ms);
	if (handle_echo(tmp->cmd, tmp, ms) == 0
		&& handle_pwd(tmp->cmd, ms->parser, ms) == 0
		&& handle_env(tmp, env, ms->parser, ms) == 0
		&& handle_export(env, 0, tmp, ms) == 0
		&& handle_cd(ms, env, tmp) == 0
		&& handle_exit(tmp->cmd, ms, env, tmp) == 0
		&& handle_unset(tmp->cmd, env, ms) == 0)
		exec_cmd(ms, tmp, env);
	else
		exit ((close_fd(ms->parser, ms), ft_free_parser(ms->parser), \
		free(ms->tab_bool), free(ms->prompt), ft_free_lexer(ms->lexer), \
		ft_free_tab(ms->path), 0));
}

void	all_cmd_gest(t_ms *ms, t_parser *tmp, char **env)
{
	tmp->pid = fork();
	if (tmp->pid < 0)
		exit ((close_fd(ms->parser, ms), \
		ft_free_tab(ms->path), perror("Error1"), 1));
	if (tmp->pid == 0)
		all_cmd_gest_2(ms, tmp, env);
	else
	{
		if (tmp->cmd && *tmp->cmd && tmp->cmd[0][0] == '.'
			&& tmp->cmd[0][1] == '/' && access(tmp->cmd[0], F_OK) == 0)
		{
			if (access(tmp->cmd[0], X_OK) == 0)
			{
				passive_sig();
				wait(NULL);
			}
		}
		close(ms->fd[ms->i - 1][0]);
		ms->fd[ms->i - 1][0] = -1;
		close(ms->fd[ms->i - 1][1]);
		ms->fd[ms->i - 1][1] = -1;
	}
}
