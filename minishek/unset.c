/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:24:26 by akaabi            #+#    #+#             */
/*   Updated: 2023/12/01 18:38:46 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_parsing(t_env **envp, char **p)
{
	t_env	*tmp;

	tmp = *envp;
	if ((!ft_isalpha(p[0][0]) && p[0][0] != '_'))
	{
		ft_putstr_fd(*p, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		(*envp)->es = 1;
		return (-1);
	}
	while (tmp)
	{
		if (tmp && p[0][0] == '_')
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}

void	unset_norm(t_env **prev, t_env **current, t_env **envp)
{
	if ((*prev))
		(*prev)->next = (*current)->next;
	else
		*envp = (*current)->next;
	free((*current)->c);
	free((*current)->v);
	free_doublep((*current)->envir);
	free((*current));
}

void	instialise_unset(t_env **prev, t_env **current, t_env **envp, char *c)
{
	*prev = NULL;
	*current = *envp;
	while (*current && ft_strcmp((*current)->c, c) != 0)
	{
		*prev = *current;
		*current = (*current)->next;
	}
	if (*current)
		unset_norm(prev, current, envp);
}

void	delete_from_env(t_env **envp, char **p)
{
	t_env	*existing;
	t_env	*prev;
	t_env	*current;
	char	*c;

	p++;
	while (*p)
	{
		if (only_alnum(*p) == 1)
		{
			if (unset_parsing(envp, p) == -1)
				return ;
			c = command_ret(*p);
			existing = find_node(*envp, c);
			if (existing)
				instialise_unset(&prev, &current, envp, c);
			free(c);
		}
		else
			free_export2((*p), envp);
		p++;
	}
}
