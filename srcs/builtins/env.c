/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:25:44 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 12:53:15 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_env2(t_parser *pa, char **env, t_parser *parser, t_ms *ms)
{
	int		i;

	i = 0;
	if (parser->file && ms->i == 0)
	{
		open_files(ms, parser);
		first_command_dup_gest(ms, parser);
	}
	if (!pa->cmd[1])
	{
		while (i < size_env(env))
		{
			if (env[i][0] != '\0' && ft_strchr(env[i], '=') != 0)
				printf("%s\n", env[i]);
			i++;
		}
	}
	close_fd(parser, ms);
	if (parser->file && ms->i == 0 && ms->nb_cmd == 1)
	{
		close (ms->history);
		exit ((close_fd(ms->parser, ms), ft_free_parser(ms->parser), \
		free(ms->tab_bool), free(ms->prompt), ft_free_lexer(ms->lexer), \
		ft_free_tab(ms->path), 0));
	}
}

int	handle_env(t_parser *pa, char **env, t_parser *parser, t_ms *ms)
{
	int		status;

	if (ft_strncmp(pa->cmd[0], "env\0", 4) == 0)
	{
		if (parser->file && ms->i == 0 && ms->nb_cmd == 1)
			parser->pid = fork();
		if (parser->pid == 0 || (!parser->file && ms->i != 0
				&& ms->nb_cmd != 1))
			handle_env2(pa, env, parser, ms);
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
