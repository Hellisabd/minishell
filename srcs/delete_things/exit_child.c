/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:46:35 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/29 12:03:15 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_child(t_ms *ms)
{
	close_fd(ms->parser, ms);
	ft_free_parser(ms->parser);
	ms->parser = NULL;
	free(ms->tab_bool);
	ms->tab_bool = NULL;
	free(ms->prompt);
	ms->prompt = NULL;
	ft_free_tab(ms->path);
	ms->path = NULL;
}
