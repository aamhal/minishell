/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:31 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/24 21:30:17 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*searching_path(char *command, t_env **envp)
{
	char	*path;
	char	**path_splied;

	path = NULL;
	if (ft_strchr(command, '/') == 0)
		return (command_slash(command, envp));
	else
	{
		path = check_env(ft_strdup("PATH"), envp);
		if (!path)
			return (NULL);
		path_splied = check_path_for_command(path, command);
		free(path);
		if (!path_splied)
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": command not found\n", 2);
			free(command);
			(*envp)->es = 127;
			exit (127);
		}
		return (path_splied[0]);
	}
}

int	builting_check(char *command)
{
	if (!ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "exit"))
		return (0);
	return (1);
}

void	simple_command(t_exec *exec_val, t_env **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	ignore_signals();
	if (pid == 0)
	{
		default_signals();
		simple_c(exec_val);
		exec_func(exec_val, envp);
	}
	waitpid(pid, &status, 0);
	catch_signals();
	(*envp)->es = exit_status(status);
	simple_cmd(&exec_val);
	return ;
}
