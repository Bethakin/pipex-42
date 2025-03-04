/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beinan <beinan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:04:34 by beinan            #+#    #+#             */
/*   Updated: 2025/03/04 18:20:04 by beinan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd[0] || !s_cmd)
	{
		free_all(s_cmd);
		err("command not found: ", cmd, 127);
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
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[4], 1);
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
		write(2,"Error: Insufficient argument.\n", 30);
		exit(0);
	}
	if (ft_strcmp(av[2], "") == 0)
		err("permission denied: ", av[2], 126);
	if (ft_strcmp(av[3], "") == 0)
		err("permission denied: ", av[3], 126);
	if (pipe(p_fd) == -1)
		err("pipe error", "", 1);
	pid = fork();
	if (pid == -1)
		err("Fork error!", "", 1);
	if (pid == 0)
		child(av, p_fd, env);
	waitpid(-1, NULL, 0);
	parent(av, p_fd, env);
}