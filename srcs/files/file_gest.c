/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:12:23 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/05/14 17:16:52 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_file	*ft_lstnew_file(char *file, int type)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return (free(file), NULL);
	new->next = NULL;
	new->filename = file;
	new->type = type;
	return (new);
}

t_file	*ft_lstlast_file(t_file *lst)
{
	t_file	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lst_add_here(t_file	**lst, t_file *new)
{
	t_file	*tmp1;
	t_file	*tmp2;

	tmp1 = *lst;
	while (tmp1 && tmp1->type != LIMITER)
		tmp1 = tmp1->next;
	if (!tmp1)
		return (ft_lstadd_front_file(lst, new));
	if (tmp1->type == LIMITER)
	{
		while (tmp1->next && tmp1->next->type == LIMITER)
			tmp1 = tmp1->next;
		tmp2 = tmp1->next;
		tmp1->next = new;
		new->next = tmp2;
	}
}

void	ft_lstadd_back_file(t_file **lst, t_file *new)
{
	t_file	*tmp;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			tmp = ft_lstlast_file(*lst);
			tmp->next = new;
		}
		new->next = NULL;
	}
}

void	file_gest(t_lexer *lexer, t_parser **parser)
{
	t_file	*file;
	char	*str;

	str = ft_strdup(lexer->str);
	if (!str)
		return ;
	file = ft_lstnew_file(str, lexer->token);
	if (file->type == LIMITER)
		ft_lst_add_here(&(*parser)->file, file);
	else
		ft_lstadd_back_file(&(*parser)->file, file);
}
