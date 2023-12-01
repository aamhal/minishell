/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:29:37 by akaabi            #+#    #+#             */
/*   Updated: 2023/12/01 17:59:50 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialination(t_exec **n, t_exec *exec_val, t_var2 *vars)
{
	(*n) = exec_val;
	(*n)->infile = STDIN_FILENO;
	(*n)->outfile = STDOUT_FILENO;
	(*n)->flag = 0;
	(*n)->flag2 = 0;
	(*n)->flag3 = 0;
	vars->i = 0;
	vars->len = 0;
	vars->s = 0;
}

int	initialination3(t_list **head, t_exec **n, t_exec **exec_val, t_env **envp)
{
	(*envp)->her_flag = 0;
	if ((*head)->sep_type == 1)
	{
		if (exec_norm(head, n, envp) == -1)
			return (-1);
	}
	else if ((*head)->sep_type == 2)
	{
		if (exec_norm4(head, n) == -1)
		{
			printf_error2(&(*head)->command[0], envp);
			(*envp)->es = 1;
			return (-1);
		}
	}
	else if ((*head)->sep_type == 3)
		exec_norm5(head, n);
	else if ((*head)->sep_type == 5)
		exec_norm6(head, n, exec_val, envp);
	else
		initialination3_norm(head, n);
	return (0);
}

void	simple_c(t_exec *exec_val)
{
	if (exec_val->infile != STDIN_FILENO)
	{
		if (exec_val->infile == -1)
			exit(1);
		dup2(exec_val->infile, STDIN_FILENO);
		close(exec_val->infile);
	}
	if (exec_val->outfile != STDOUT_FILENO)
	{
		dup2(exec_val->outfile, STDOUT_FILENO);
		close(exec_val->outfile);
	}
}
