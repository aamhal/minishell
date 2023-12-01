/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:03:03 by akaabi            #+#    #+#             */
/*   Updated: 2023/11/30 09:21:06 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_func(t_exec *exec_val, t_env **envp)
{
	char	*path;

	if (!builting_check(exec_val->command[0]))
	{
		builting(&exec_val, envp, exec_val->outfile);
		exit (0);
	}
	path = searching_path(exec_val->command[0], envp);
	if (!path)
	{
		printf_error(exec_val->command[0], envp);
		exit(127);
	}
	if (exec_val && exec_val->command[0][0] == '\0')
		free_empty_c(&exec_val);
	free(exec_val->command[0]);
	exec_val->command[0] = ft_strdup(path);
	free(path);
	(*envp)->es = 0;
	if (execve(exec_val->command[0], exec_val->command, (*envp)->envir) == -1)
	{
		free(exec_val->command[0]);
		free(exec_val->command);
		exit (1);
	}
}

void	printf_error(char *s, t_env **env)
{
	(*env)->es = 127;
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

void	for_here_doc(char *Delim, int fd, t_env **env)
{
	char	*cmd;

	default_signals();
	while (1)
	{
		cmd = readline("Heredoc> ");
		if (Delim)
		{
			if (!ft_strcmp(cmd, Delim))
			{
				free(cmd);
				exit(0);
			}
		}
		cmd = her_fill(cmd, env);
		ft_putstr_fd(cmd, fd);
		write(fd, "\n", 1);
		free(cmd);
	}
}

void	simple_cmd(t_exec **exec_val)
{
	if ((*exec_val)->infile != STDIN_FILENO)
		close((*exec_val)->infile);
	if ((*exec_val)->outfile != STDOUT_FILENO)
		close((*exec_val)->outfile);
}

void	first(t_exec *exec_val, int **fd)
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
	else
		dup2(fd[0][1], STDOUT_FILENO);
}
