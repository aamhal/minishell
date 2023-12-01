/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 08:07:42 by aamhal            #+#    #+#             */
/*   Updated: 2023/12/01 18:29:33 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_path2(char *path)
{
	char	*p; 
	int		i;
	int		j;
	char	*x;

	p = ft_strrchr(path, '/');
	i = ft_strlen(path);
	j = ft_strlen(p);
	if (j == i)
		i++;
	x = ft_substr(path, 0, (i - j));
	free(path);
	return (x);
}

char	*check_ex(char *p)
{
	int		i;
	char	c;
	int		count;

	i = 0;
	count = 0;
	if (p[0] == '\'' || p[0] == '\"')
		c = p[0];
	while (p[i])
	{
		if (p[i] == '\'' && c == '\"')
			return (0);
		else if (p[i] == '\"' && c == '\'')
			return (0);
		else if (p[i] == c)
			break ;
		count++;
		i++;
	}
	while (count--)
		p = q_remouve(p, 0, 0);
	return (p);
}

void	printf_error2(char *s, t_env **env)
{
	(*env)->es = 127;
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("No such file or directory", 2);
	ft_putstr_fd("\n", 2);
}

int	check_split(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (!ft_strcmp(p[i], ".."))
			return (-1);
		i++;
	}
	return (0);
}
