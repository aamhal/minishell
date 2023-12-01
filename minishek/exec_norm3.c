/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:14:30 by akaabi            #+#    #+#             */
/*   Updated: 2023/12/01 18:34:01 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_norm(t_exec *tmp, t_env **envp, int data)
{
	char	*path;

	if (!ft_strcmp(tmp->command[0], "export"))
	{
		if (!tmp->command[1])
			print_node_export((*envp), data);
		else
			update_or_add_env(envp, tmp->command);
	}
	else if (!ft_strcmp(tmp->command[0], "unset"))
		delete_from_env(envp, tmp->command);
	else if (!ft_strcmp(tmp->command[0], "env"))
	{
		path = check_env(ft_strdup("PATH"), envp);
		if (!path && (*envp)->f_env == 0)
		{
			ft_putstr_fd("env: No such file or directory\n", 2);
			(*envp)->es = 127;
			return ;
		}
		free(path);
		print_nodes(*envp, data);
	}
	else
		b_norm2(tmp, envp, data);
}

void	b_norm2(t_exec *tmp, t_env **envp, int data)
{
	if (!ft_strcmp(tmp->command[0], "echo"))
		echo_command(tmp->command, data, envp);
	else if (!ft_strcmp(tmp->command[0], "cd"))
		cd_command(tmp->command, envp);
	else if (tmp->command[0][0] == 'p' || tmp->command[0][0] == 'P')
		pwd_command(tmp->command[0], envp, data);
	else if (!ft_strcmp(tmp->command[0], "exit"))
		exit_command(tmp->command);
}

int	exec_norm(t_list **head, t_exec **n, t_env **envp)
{
	(*head) = (*head)->next;
	(*n)->flag2 = 1;
	if ((*n)->outfile != STDOUT_FILENO)
	{
		close((*n)->outfile);
		(*n)->outfile = redirection_out((*head)->command);
	}
	else
		(*n)->outfile = redirection_out((*head)->command);
	if ((*n)->outfile == -1)
	{
		(*envp)->es = 1;
		return (-1);
	}
	return (0);
}

void	exec_norm2(t_list	**head, t_exec **n)
{
	t_list	*current;
	t_var2	vars;

	vars.i = 0;
	current = *head;
	while (current && current->type == 'W')
	{
		current = current->next;
		vars.i++;
	}
	vars.len = vars.i;
	vars.i = 0;
	(*n)->command = malloc(sizeof(char *) * (vars.len + 1));
	(*n)->command[vars.len] = NULL; 
	while (head && vars.i < vars.len)
	{
		(*n)->command[vars.i] = ft_strdup((*head)->command);
		if (vars.i < vars.len - 1)
			(*head) = (*head)->next;
		vars.i++;
	}
	(*n)->command = resize_char((*n)->command);
	(*n)->flag = 1;
}

void	exec_norm3(t_list **list, t_exec **n)
{
	t_list	*head;

	head = (*list);
	if (head->sep_type == 4)
	{
		(*n)->next = malloc(sizeof(t_exec));
		(*n)->next->infile = STDIN_FILENO;
		(*n)->next->outfile = STDOUT_FILENO;
		(*n) = (*n)->next;
	}
}
