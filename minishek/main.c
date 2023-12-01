/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:29:08 by aamhal            #+#    #+#             */
/*   Updated: 2023/12/01 17:57:32 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_null(void)
{
	char	**envp;
	char	*pwd;
	char	path[1024];

	pwd = getcwd(path, sizeof(path));
	envp = malloc(sizeof(char *) * 4);
	envp[3] = NULL;
	envp[1] = ft_strjoin(ft_strdup("PWD="), ft_strdup(pwd));
	envp[0] = "SHLVL=1";
	envp[2] = "_=/usr/bin/env";
	return (envp);
}

char	**env_exist(char **env)
{
	char	**envp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	envp = malloc(sizeof(char *) * (i + 1));
	envp[i] = NULL;
	j = i;
	i = 0;
	while (i < j)
	{
		envp[i] = env[i];
		i++;
	}
	return (envp);
}

int	main(int ac, char **av, char **env)
{
	t_env	*head;
	t_list	*list;
	char	**envp;
	int		flag;

	(void)ac;
	(void)av;
	flag = 0;
	head = NULL;
	list = NULL;
	catch_signals();
	if (!(*env))
	{
		envp = env_null();
		flag = 1;
	}
	else
		envp = env_exist(env);
	parsing(&list, &head, envp, flag);
	return (0);
}
