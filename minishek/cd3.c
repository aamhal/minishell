/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:53:34 by aamhal            #+#    #+#             */
/*   Updated: 2023/12/01 18:28:53 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_back_free(char *p)
{
	free(p);
	return (ft_strdup("/"));
}

void	r_q(t_list **list)
{
	t_list	*tmp;

	tmp = (*list);
	while (tmp)
	{
		tmp->command = q_remouve(tmp->command, 0, 0);
		tmp = tmp->next;
	}
}

void	while_expand(t_list **tmp, t_env **env)
{
	int	i;

	i = 0;
	while ((*tmp)->command[i])
	{
		if ((*tmp)->command[i] == '\"' && (*tmp)->command[i + 1] == '$' \
		&& (*tmp)->command[i + 2] == '\"')
			break ;
		if ((*tmp)->command[i] == '$' && (*tmp)->command[i + 1] == '\0')
			break ;
		if ((*tmp)->command[i] == '$' && (*tmp)->command[i + 1] == '?')
		{
			free((*tmp)->command);
			(*tmp)->command = ft_itoa((*env)->es);
			break ;
		}
		if ((*tmp)->command[i] == '$')
		{
			(*env)->flag = 1;
			check_expand((*tmp), env);
			break ;
		}
		i++;
	}
}
