/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:06:12 by akaabi            #+#    #+#             */
/*   Updated: 2023/12/01 17:41:19 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiple_command(t_exec *exec_val, t_env **envp, int i)
{
	pid_t	pid[3];
	int		n;
	int		**fd;
	int		status;

	n = list_size(exec_val);
	fd = make_fd(n);
	multi_cmd_fd(fd);
	i = 1;
	pid[0] = first_child(exec_val, envp, fd);
	exec_val = exec_val->next;
	while (i < n - 1)
	{
		pid[1] = middle_child(exec_val, envp, fd, i);
		exec_val = exec_val->next;
		i++;
	}
	pid[2] = last_child(exec_val, envp, fd, (i - 1));
	multi_cmd_fd_close(fd);
	i = 0;
	while (i < 3)
		waitpid(pid[i++], &status, 0);
	catch_signals();
	(*envp)->es = exit_status(status);
	free_double(fd);
}

void	free_list_exe(t_exec **list)
{
	int	i;

	i = 0;
	if (!(*list))
		return ;
	if ((*list)->next)
		free_list_exe(&(*list)->next);
	while ((*list)->command && (*list)->command[i])
	{
		free((*list)->command[i]);
		i++;
	}
	free((*list)->command);
	free(*list);
	*list = NULL;
}

char	*command_slash(char *command, t_env **env)
{
	if (opendir(command))
	{
		write(2, command, ft_strlen(command));
		write(2, ": is a directory\n", 17);
		exit(126);
	}
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	printf_error(command, env);
	return (NULL);
}

void	free_doublep(char **command)
{
	int	i;

	if (!command)
		return ;
	i = 0;
	while (command && command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}
