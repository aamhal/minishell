/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:16:34 by akaabi            #+#    #+#             */
/*   Updated: 2023/12/01 17:48:58 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_ofenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

t_env	*filling_env(t_env *a, char **env)
{
	int	i;
	int	size;

	i = 0;
	size = size_ofenv(env);
	a->envir = malloc(sizeof(char *) * (size + 1));
	while (env[i])
	{
		a->envir[i] = ft_strdup(env[i]);
		i++;
	}
	a->envir[i] = NULL;
	return (a);
}

t_env	*fill_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_env;
	int		i;
	int		j;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return (0);
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		env_norm(&new_env, envp, &i, &j);
		env_norm2(&head, &current, &new_env);
		i++;
	}
	head = filling_env(head, envp);
	return (head);
}

int	fun(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				return (1);
		}
		i++;
	}
	return (0);
}

int	only_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '=')
				return (1);
			else
				return (0);
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
