/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:03:50 by aamhal            #+#    #+#             */
/*   Updated: 2023/11/30 13:11:55 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_command(char **command, int fd, t_env **env)
{
	int	i;

	i = check_option_echo(command);
	(*env)->es = 0;
	if (!command[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (!check_echo_n(command[1]))
	{
		while (command[i])
		{
			ft_putstr_fd(command[i], fd);
			if (command[i + 1])
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	else 
		echo_norm(command, fd);
}

void	echo_norm(char **command, int fd)
{
	int	f;
	int	i;

	i = 1;
	f = 1;
	while (command[i])
	{
		if (ft_strcmp(command[i], "-"))
		{
			ft_putstr_fd(command[i], fd);
			if (command[i + 1])
				ft_putchar_fd(' ', fd);
		}
		i++;
	}
	if (f == 1)
		ft_putchar_fd('\n', fd);
}

int	check_echo_n(char *str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str, "-"))
		return (-1);
	if (str[i] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (-1);
			i++;
		}
		return (0);
	}
	else
		return (-1);
}

int	check_option_echo(char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		if (check_echo_n(command[i]) == -1)
			break ;
		i++;
	}
	return (i);
}
