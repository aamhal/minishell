/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:56:53 by akaabi            #+#    #+#             */
/*   Updated: 2023/12/01 17:26:55 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	redirection_out(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	redirection_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	here_doc(char *Delim, t_env **env)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	ignore_signals();
	pid = fork();
	if (pid == 0)
		for_here_doc(Delim, fd[1], env);
	waitpid(pid, &status, 0);
	if (status == 2)
	{
		catch_signals();
		close (fd[1]);
		close(fd[0]);
		return (-1);
	}
	close (fd[1]);
	(*env)->her_flag = 1;
	return (fd[0]);
}

int	list_size(t_exec *exec_val)
{
	t_exec	*head;
	int		size;

	if (!exec_val)
		return (0);
	size = 0;
	head = exec_val;
	while (head)
	{
		size++;
		head = head ->next;
	}
	return (size);
}
