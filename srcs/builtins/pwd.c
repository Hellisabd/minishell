/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:18:44 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 12:53:34 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_pwd2(t_parser *parser, t_ms *ms)
{
	char	cwd[1024];

	if (parser->file && ms->i == 0)
	{
		open_files(ms, parser);
		first_command_dup_gest(ms, parser);
	}
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	close_fd(parser, ms);
	if (parser->file && ms->i == 0 && ms->nb_cmd == 1)
	{
		close(ms->history);
		exit ((exit_child(ms), 0));
	}
}

int	handle_pwd(char **cmd, t_parser *parser, t_ms *ms)
{
	int		status;

	if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
	{
		if (parser->file && ms->i == 0 && ms->nb_cmd == 1)
			parser->pid = fork();
		if (parser->pid == 0 || (!parser->file && ms->i != 0
				&& ms->nb_cmd != 1))
			handle_pwd2(parser, ms);
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

void	actual_pwd(char *str, char **env, t_ms *ms, int i)
{
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			if (ms->tab_bool[i] == true)
				free(env[i]);
			else
				ms->tab_bool[i] = true;
			env[i] = ft_strjoin_const("OLDPWD=", ms->dir);
			if (!env[i])
				return ;
		}
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			if (ms->tab_bool[i] == true)
				free(env[i]);
			else
				ms->tab_bool[i] = true;
			env[i] = ft_strjoin_const("PWD=", str);
			if (!env[i])
				return ;
		}
		i++;
	}
}
