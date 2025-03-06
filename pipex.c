/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beinan <beinan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:04:34 by beinan            #+#    #+#             */
/*   Updated: 2025/03/06 20:57:14 by beinan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_command(char *cmd, char **s_cmd)
{
	if (!s_cmd[0] || !s_cmd)
	{
		free_all(s_cmd);
		err("command not found: ", cmd, 127);
	}
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	validate_command(cmd, s_cmd);
	if (cmd[0] == '/')
	{
		if (execve(cmd, s_cmd, env) == -1)
		{
			perror("Error");
			free_all(s_cmd);
			exit(0);
		}
	}
	path = get_path(s_cmd[0], env);
	if (path == 0)
	{
		free_all(s_cmd);
		err("command not found: ", cmd, 127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		free_all(s_cmd);
		err("command not found: ", cmd, 127);
	}
}

void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[1], 0);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[4], 1);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		write(2, "Error: Insufficient argument.\n", 30);
		exit(0);
	}
	if (ft_strcmp(av[2], "") == 0 || ft_strcmp(av[3], "") == 0)
		err("permission denied: ", "", 126);
	if (pipe(p_fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pid == 0)
		child(av, p_fd, env);
	waitpid(-1, NULL, 0);
	parent(av, p_fd, env);
}
