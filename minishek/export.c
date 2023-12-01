/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:18:19 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/24 10:09:41 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_node(t_env *head, char *command)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (!ft_strcmp(current->c, command))
			return (current);
		current = current->next;
	}
	return (0);
}

char	*command_ret(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	s = malloc(i + 1);
	if (!s)
		return (0);
	j = 0;
	while (str[j] && j < i)
	{
		s[j] = str[j];
		j++;
	}
	s[i] = '\0';
	return (s);
}

char	*value_ret(char *str)
{
	char	*s;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (0);
	i++;
	s = ft_substr(str, i, ft_strlen(str) - i);
	return (s);
}

void	update_or_add_env(t_env **envp, char **p)
{
	t_env	*existing;
	t_env	*new_env;
	t_var3	*vars;

	p = u_a_envnorm(&vars, &new_env, p);
	while (*p)
	{
		if (only_alnum(*p) == 1)
		{
			export_initialisation(p, &vars, envp, &existing);
			if (existing)
				existing_norm(p, &vars, &existing);
			else if (not_exesting_norm(new_env, &vars, p, envp) == -1)
				return (free(vars));
		}
		else
		{
			free_export2(*p, envp);
			return (free(vars));
		}
		p++;
	}
	free(vars);
}
