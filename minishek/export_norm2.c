/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:04:56 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/24 10:43:06 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_export2(char *p, t_env **envp)
{
	ft_putstr_fd(p, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	(*envp)->es = 1;
}

char	**u_a_envnorm(t_var3 **vars, t_env **new_env, char **p)
{
	(*vars) = malloc(sizeof(t_var3));
	(*new_env) = NULL;
	p++;
	return (p);
}
