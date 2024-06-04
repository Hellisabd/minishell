/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:14:07 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 10:36:19 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	printvar(char *str)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (str[i])
	{
		printf("%c", str[i]);
		if (str[i] == '=')
			printf("\"");
		i++;
	}
	if (ft_strchr(str, '=') != 0)
		printf("\"");
	printf("\n");
}

void	ft_add_back_export(t_export **ex, char *str)
{
	t_export	*tmp;
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		exit(EXIT_FAILURE);
	new->var = ft_strdup(str);
	new->rank = -1;
	new->ranked = 0;
	new->next = NULL;
	if (ex == NULL || *ex == NULL)
	{
		*ex = new;
		return ;
	}
	tmp = *ex;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	find_diff2(t_export **tmp, char c, t_export **save)
{
	while (*tmp)
	{
		if (!(*save) && (*tmp)->var[0] == c && (*tmp)->ranked == 0)
			*save = *tmp;
		else if (*save && (*tmp)->var[0] == c && same_char((*save)->var, \
			(*tmp)->var) == 1 && (*tmp)->ranked == 0)
			*save = *tmp;
		*tmp = (*tmp)->next;
	}
}

void	ft_find_diff(t_export *ex)
{
	t_export	*tmp;
	t_export	*save;
	char		c;
	int			i;

	i = 0;
	c = 'A';
	while (c != 'z' + 1)
	{
		tmp = ex;
		save = NULL;
		find_diff2(&tmp, c, &save);
		if (save)
		{
			save->ranked = 1;
			save->rank = i;
			i++;
		}
		else if (c == 'Z')
			c = 'a';
		else
			c++;
	}
}

int	print_export(char **env)
{
	t_export	*export;
	t_export	*tmp;
	int			i;

	i = -1;
	export = NULL;
	while (++i < size_env(env))
		ft_add_back_export(&export, env[i]);
	i = 0;
	ft_find_diff(export);
	tmp = export;
	while (tmp)
	{
		if (tmp->rank == i)
		{
			printvar(tmp->var);
			tmp = export;
			i++;
		}
		else
			tmp = tmp->next;
	}
	free_exlist(export);
	return (0);
}
