/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:12:19 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 12:54:58 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	first_command_dup_gest(t_ms *ms, t_parser *gest)
{
	if (gest->fdin != 0)
	{
		if (dup2(gest->fdin, 0) < 0)
			exit ((close_fd(ms->parser, ms), \
			ft_free_tab(ms->path), perror("dup failed"), exit_child(ms), 1));
	}
	else if (gest->fd[0] != -1 && check_last_file(gest->file) == LIMITER)
	{
		if (0 > dup2(gest->fd[0], 0))
			exit ((ft_free_tab(ms->path), close_fd(ms->parser, ms), \
			perror("dup failed"), exit_child(ms), 1));
	}
	if (ms->fd && gest->fdout == 1)
	{
		if (dup2(ms->fd[0][1], 1) < 0)
			exit ((close_fd(ms->parser, ms), ft_free_tab(ms->path), \
			perror("dup failed"), exit_child(ms), 1));
	}
	else
	{
		if (dup2(gest->fdout, 1) < 0)
			exit ((close_fd(ms->parser, ms), ft_free_tab(ms->path), \
			perror("dup failed"), exit_child(ms), 1));
	}
}

void	first_command(t_ms *ms, t_parser *gest, char **env)
{
	gest->pid = fork();
	if (gest->pid == 0)
	{
		close(ms->history);
		if (gest->cmd && *gest->cmd && gest->cmd[0][0] == '.'
			&& gest->cmd[0][1] == '/'
			&& gest->cmd && gest->cmd && access(gest->cmd[0], F_OK) == 0)
			if (access(gest->cmd[0], X_OK) == 0)
				passive_sig();
		first_command_dup_gest((open_files(ms, gest), ms), gest);
		if (handle_echo(gest->cmd, gest, ms) == 0
			&& handle_pwd(gest->cmd, ms->parser, ms) == 0
			&& handle_env(gest, env, ms->parser, ms) == 0
			&& handle_export(env, 0, gest, ms) == 0
			&& handle_unset(gest->cmd, env, ms) == 0
			&& handle_cd(ms, env, gest) == 0
			&& handle_exit(gest->cmd, ms, env, gest) == 0)
			exec_cmd(ms, gest, env);
		else
			exit ((exit_child(ms), 0));
	}
	else
		if (gest->cmd && *gest->cmd && access(gest->cmd[0], F_OK) == 0)
			if (access(gest->cmd[0], X_OK) == 0)
				sig_wait();
}
