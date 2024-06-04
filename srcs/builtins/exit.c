/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:30:36 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/29 12:09:24 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_exit(t_ms *ms, char *check, int b, t_parser *parser)
{
	int	e;

	if (ms->nb_cmd == 1)
		ft_putstr_fd("exit\n", 1);
	close (ms->history);
	close_fd(ms->parser, ms);
	free(ms->tab_bool);
	free(ms->prompt);
	if (b == 0)
		exit ((free(check), ft_free_lexer(ms->lexer), \
		ft_free_parser(ms->parser), ft_free_tab(ms->path), 2));
	if (b == 1)
	{
		if (parser->cmd[1] != NULL)
		{
			e = ft_atoi(check);
			exit ((free(check), ft_free_lexer(ms->lexer), \
				ft_free_parser(ms->parser), ft_free_tab(ms->path), e));
		}
		else
			exit ((free(check), ft_free_lexer(ms->lexer), \
			ft_free_parser(ms->parser), ft_free_tab(ms->path), 0));
	}
}

int	count_cmd(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->cmd[i])
		i++;
	return (i);
}

void	handle_exit2(char **cmd, t_ms *ms, char *check, t_parser *parser)
{
	if (ft_strncmp(cmd[1] + 1, check, ft_strlen(cmd[1])) == 0)
		free_exit(ms, check, 1, parser);
	else
	{
		exit_err("exit: ", cmd[1], "numeric argument required\n", 1);
		free_exit(ms, check, 0, parser);
	}
}

int	handle_exit(char **cmd, t_ms *ms, char **env, t_parser *parser)
{
	char	*check;

	check = NULL;
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
	{
		if (count_cmd(ms->parser) > 2 && ft_strisdigit(cmd[1]) == 1)
			return (printf("exit\n"), exit_err("exit: ", cmd[1], \
			"too many arguments\n", 0), ms->e_s = 1, 1);
		else if (cmd[1])
		{
			check = ft_itoa(ft_atoi(cmd[1]));
			if (!check)
				return (0);
		}
		if (cmd[1] == NULL || ft_strncmp(cmd[1], check, ft_strlen(cmd[1])) == 0)
			free_exit((ft_free_env(ms, env), ms), check, 1, parser);
		else if (cmd[1][0] == '+')
			handle_exit2((ft_free_env(ms, env), cmd), ms, check, parser);
		else if (ft_strncmp(cmd[1], check, ft_strlen(cmd[1])) != 0)
			free_exit((ft_free_env(ms, env), exit_err("exit: ", cmd[1], \
			"numeric argument required\n", 1), ms), check, 0, parser);
		return (1);
	}
	return (0);
}
