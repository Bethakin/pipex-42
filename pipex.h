/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beinan <beinan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:04:43 by beinan            #+#    #+#             */
/*   Updated: 2025/03/06 20:57:33 by beinan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

int		open_file(char *file, int n);
size_t	where_is(char *arg, char needle);
void	validate_command(char *cmd, char **s_cmd);
void	child(char **av, int *p_fd, char **env);
void	parent(char **av, int *p_fd, char **env);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	free_all(char **tab);
int		ft_strcmp(const char *s1, const char *s2);
void	err(char *err, char *a, int exit_code);
void	command_check(char *arg);

#endif
