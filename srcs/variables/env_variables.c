/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:21:48 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/22 12:39:21 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_err(t_lexer *tmp)
{
	if (tmp && tmp->str && tmp->str[0] == '|')
		return (ft_putstr_fd \
			("minishell: syntax error near unexpected token `newline'\n"\
			, 2), -1);
	else
	{
		while (tmp)
		{
			if (tmp->next && tmp->str && tmp->token == PIPE
				&& tmp->next->token == PIPE)
				return (ft_putstr_fd \
				("minishell: syntax error near unexpected token `newline'\n"\
				, 2), -1);
			tmp = tmp->next;
		}
	}
	return (0);
}

int	set_new_env(char **env)
{
	int		i;
	char	*tmp;
	int		nbr;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			tmp = ft_strstartdup(env[i], 6);
			if (!tmp)
				return (0);
			nbr = ft_atoi(tmp) + 1;
			free(tmp);
			tmp = ft_itoa(nbr);
			if (!tmp)
				return (0);
			nbr = ft_strlen(env[i]);
			while (--nbr >= 6)
				env[i][nbr] = '\0';
			ft_strlcat(env[i], tmp, ft_strlen(env[i]) + ft_strlen(tmp) + 1);
			free (tmp);
		}
	}
	return (1);
}
