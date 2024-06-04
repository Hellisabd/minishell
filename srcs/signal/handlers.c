/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:59:42 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/30 10:41:07 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig(t_ms *ms)
{
	if (g_e_s == 130)
	{
		g_e_s = 0;
		ms->e_s = 130;
	}
	if (g_e_s == 131)
	{
		g_e_s = 0;
		ms->e_s = 131;
	}
}

void	child(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		g_e_s = 130;
	}
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDERR_FILENO);
		g_e_s = 131;
	}
}

void	parent(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_e_s = 130;
	}
}

void	h_s(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		close(STDOUT_FILENO);
		g_e_s = 130;
	}
}
