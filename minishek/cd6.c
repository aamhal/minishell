/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd6.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:25:16 by aamhal            #+#    #+#             */
/*   Updated: 2023/12/01 18:29:50 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_command_norm(int flag, char **p)
{
	if (flag == -1)
	{
		free_split(p);
		return (-1);
	}
	free_split(p);
	return (0);
}

int	check_s(char *p)
{
	int	i;

	i = 0;
	if (p[0] != '\0')
	{
		while (p[i])
		{
			if (p[i] == ' ')
				return (-1);
			i++;
		}
	}
	return (0);
}

char	**resize_char(char **p)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (check_s(p[0]) == 0)
		return (p);
	cmd = ft_split(p[0], ' ');
	free_doublep(p);
	return (cmd);
}
