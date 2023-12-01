/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:14:38 by aamhal            #+#    #+#             */
/*   Updated: 2023/12/01 18:29:11 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_loop(char **p, t_env **env)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] && !ft_strcmp(p[i], ".."))
			cd_back(env);
		else if (p[i] && ft_strcmp(p[i], "."))
			cd_next(p[i], env);
		i++;
	}
}

char	*check_env_cd(char *p, t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(p, tmp->c))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (p);
	return (tmp->v);
}

void	cdhome_norm(t_env *tmp, char **home, t_env **env)
{
	while (tmp)
	{
		if (!ft_strcmp("PWD", tmp->c))
		{
			free(*home);
			free(tmp->v);
			tmp->v = check_env(ft_strdup("HOME"), env);
		}
		tmp = tmp->next;
	}
}

void	cdback_norm(t_env *envp, char **opwd)
{
	while (envp)
	{
		if (!ft_strcmp("PWD", envp->c))
		{
			free(envp->v);
			envp->v = ft_strjoin(ft_strdup(""), *opwd);
		}
		envp = envp->next;
	}
}

void	cdnext_norm(t_env *envp, char *command)
{
	while (envp)
	{
		if (!ft_strcmp("PWD", envp->c))
		{
			if (ft_strcmp(envp->v, "/"))
				envp->v = ft_strjoin(envp->v, ft_strdup("/"));
			envp->v = ft_strjoin(envp->v, ft_strdup(command));
		}
		envp = envp->next;
	}
}
