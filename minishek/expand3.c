/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:09:12 by aamhal            #+#    #+#             */
/*   Updated: 2023/12/01 18:38:27 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_expand(t_list *tmp, t_env **env)
{
	int		i;
	int		j;
	t_var1	*var;

	var = malloc(sizeof(t_var1));
	i = 0;
	j = 0;
	var->flag = 0;
	while (tmp->command[i] && tmp->command[i] != '$')
		i++;
	var->p = ft_substr(tmp->command, j, i - j);
	while (tmp->command[i])
	{
		i++;
		var->p = ft_strjoin(var->p, special_expand2(tmp->command, &i, var));
		normal_expand_helper2_norm(tmp->command, var, env, &i);
		var->flag = 0;
	}
	free(tmp->command);
	tmp->command = ft_strjoin(ft_strdup(""), var->p);
	free(var);
}

char	*normal_expand_helper1(char *s, t_env **env)
{
	int		i;
	int		j;
	char	*p;
	t_var1	*var;

	init_expand(&i, &j, &var, s);
	p = ft_substr(s, j, i - j);
	while (s[i])
	{
		i++;
		p = ft_strjoin(p, special_expand2(s, &i, var));
		j = i;
		while (s[i] && s[i] != '$')
			i++;
		if (var->flag == 0)
			var->x = check_env(ft_substr(s, j, i - j), env);
		else 
			var->x = ft_substr(s, j, i - j);
		if (var->x)
			p = ft_strjoin(p, var->x);
		j = i;
		normal_expand_helper1_norm(s, &i, var, &p);
	}
	return (free(s), free(var), p);
}

char	*normal_expand_helper2(char *s, t_env **env)
{
	int		i;
	int		j;
	char	*p;
	t_var1	*var;

	var = malloc(sizeof(t_var1));
	i = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		i++;
	var->p = ft_substr(s, j, i - j);
	while (s[i])
	{
		i++;
		var->p = ft_strjoin(var->p, special_expand2(s, &i, var));
		j = i;
		normal_expand_helper2_norm(s, var, env, &i);
		var->flag = 0;
	}
	free(s);
	p = ft_strjoin(var->p, ft_strdup(""));
	free(var);
	return (p);
}
