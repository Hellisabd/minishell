/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:05:19 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/21 13:06:01 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dollar_question(t_expand *ex, t_ms *ms)
{
	char	*tmp;

	tmp = ft_itoa(ms->e_s);
	if (!tmp)
		return ;
	ex->line = ft_strjoin(ex->line, tmp);
	if (!ex->line)
		return ;
	ex->i = ex->i + 2;
	free(tmp);
}

void	expandables4(t_expand *ex)
{
	ex->line = ft_strjoin(ex->line, "$");
	if (!ex->line)
		return ;
	ex->i++;
}
