/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:24:57 by amirloup          #+#    #+#             */
/*   Updated: 2024/05/30 13:15:20 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_unset2(char **cmd, char **env, t_ms *ms, t_ms *count)
{
	if (ft_strncmp(cmd[count->n], count->tmp, ft_strlen(cmd[count->n])) == 0 && \
	ft_strncmp(cmd[count->n], count->tmp, ft_strlen(count->tmp)) == 0)
	{
		if (ms->tab_bool[count->i] == true)
		{
			free(env[count->i]);
			env[count->i] = malloc(1);
			env[count->i][0] = '\0';
		}
		else
			env[count->i][0] = '\0';
	}
}

char	*extract_var(char *s)
{
	int		i;
	int		j;
	char	*dest;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	dest = (char *)malloc (sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	while (s[j] != '\0' && j < i)
	{
		dest[j] = s[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

int	handle_unset(char **cmd, char **env, t_ms *ms)
{
	t_ms	count;

	count.n = 0;
	if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
	{
		while (cmd[++count.n])
		{
			count.i = -1;
			while (env[++count.i])
			{
				count.tmp = extract_var(env[count.i]);
				if (!count.tmp)
					return (0);
				handle_unset2(cmd, env, ms, &count);
				free(count.tmp);
			}
		}
		ms->e_s = 0;
		return (1);
	}
	return (0);
}
