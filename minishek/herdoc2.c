/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 22:13:55 by aamhal            #+#    #+#             */
/*   Updated: 2023/11/30 09:03:02 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*her_fill(char *p, t_env **env)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = NULL;
	while (p[i])
	{
		if (p[i] == '$')
		{
			if ((*env)->f_expand == 0)
			{
				tmp = ft_lstnew(ft_strdup(p));
				expand(&tmp, env);
				free(p);
				p = ft_strdup(tmp->command);
				free(tmp->command);
				free(tmp);
			}
		}
		i++;
	}
	return (p);
}

void	initialination3_norm(t_list **head, t_exec **n)
{
	if ((*head)->type == 'W')
		exec_norm2(head, n);
	else if ((*head)->sep_type == 4)
		exec_norm7(n);
}

void	init_expand(int *i, int *j, t_var1 **var, char *s)
{
	*var = malloc(sizeof(t_var1));
	*i = 0;
	*j = 0;
	(*var)->flag = 0;
	while (s[*i] && s[*i] != '$')
		(*i)++;
}
