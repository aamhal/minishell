/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:38:14 by aamhal            #+#    #+#             */
/*   Updated: 2023/12/01 18:27:16 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_separ(t_list **list, char *separ)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, separ) && tmp->type == 'S')
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}

int	check_if_her(t_list **list, char *separ)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, separ) && tmp->type == 'S')
		{
			tmp = tmp->next;
			if (tmp->command[0] == '\'' || tmp->command[0] == '\"')
				return (-1);
			else
				return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	free_empty_c(t_exec **exec_val)
{
	printf(" : command not found\n");
	free((*exec_val)->command[0]);
	free((*exec_val)->command);
	exit (127);
}

void	closing_fds(t_exec **n)
{
	if ((*n)->outfile != STDOUT_FILENO)
		close ((*n)->outfile);
	if ((*n)->infile != STDIN_FILENO)
		close ((*n)->infile);
}

void	norm_shito(t_exec **n, t_exec **exec_val, t_env *envp)
{
	(void)exec_val;
	(void)envp;
	closing_fds(n);
	free_list_exe(n);
}
