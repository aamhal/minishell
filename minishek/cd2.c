/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:34:29 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/22 22:56:30 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **p)
{
	int		i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

char	*ft_path(t_env **env)
{
	char	*path;
	char	*p; 
	int		i;
	int		j;
	char	*x;

	path = check_env(ft_strdup("PWD"), env);
	p = ft_strrchr(path, '/'); 
	i = ft_strlen(path);
	j = ft_strlen(p);
	x = ft_substr(path, 0, (i - j));
	free(path);
	return (x);
}

void	cd_slash(t_env **env)
{
	t_env	*envp;
	char	*path;
	char	*cwd;
	size_t	size;

	envp = (*env);
	path = NULL;
	size = 0;
	if (cd_error("/", 1, env) == -1)
		return ;
	cd_next_env(envp, env);
	cwd = getcwd(path, size);
	if (cwd != NULL)
	{
		while (envp)
		{
			if (!ft_strcmp("PWD", envp->c))
			{
				free(cwd);
				free(envp->v);
				envp->v = ft_strdup("/");
			}
			envp = envp->next;
		}
	}
}

char	*last_slash(char *p)
{
	int		i;
	int		len;
	char	*x;

	i = 0;
	len = ft_strlen(p);
	if (p[len - 1] != '/')
		return (ft_strdup(p));
	x = malloc(len);
	x[len - 1] = '\0';
	while (len - 1 > i)
	{
		x[i] = p[i];
		i++;
	}
	return (x);
}

int	cd_error(char *p, int f, t_env **env)
{
	if (access(p, F_OK) == -1)
	{
		if (f == 1)
		{
			perror("access");
		}
		(*env)->es = 1;
		return (-1);
	}
	if (chdir(p) != 0)
	{
		perror("chdir");
		return (-1);
	}
	return (0);
}
