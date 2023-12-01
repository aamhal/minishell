/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_hundle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:52:51 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/23 21:45:44 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*q_remouve(char *str, int i, int j)
{
	char	*p;
	char	*x;

	x = ft_strdup("");
	while (str[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			j = i;
			i = find_index(str, i);
			p = ft_substr(str, j + 1, i - j - 1);
			x = ft_strjoin(x, p);
		}
		else
		{
			j = i;
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			p = ft_substr(str, j, i - j);
			x = ft_strjoin(x, p);
			i--;
		}
		i++;
	}
	return (free(str), x);
}

void	r_q_norm(char *str, char **p, int *i, int *j)
{
	(*p)[*j] = str[*i];
	*i = *i + 1;
	*j = *j + 1;
}
