/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:16:36 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/03 10:50:01 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	g_e_s = 0;

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_ms	ms;

	(void)argv;
	argc = 0;
	ms.history = open("history.txt", O_RDWR | O_APPEND, 0644);
	line = get_next_line(ms.history);
	line = ft_strtrim(line, "\n");
	while (line)
	{
		add_history(line);
		free(line);
		line = get_next_line(ms.history);
		line = ft_strtrim(line, "\n");
	}
	prompt(env, ms.history);
}
