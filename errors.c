/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beinan <beinan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:40:14 by beinan            #+#    #+#             */
/*   Updated: 2025/03/06 20:57:22 by beinan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err(char *err, char *a, int exit_code)
{
	int	i;

	i = 0;
	ft_putstr_fd(err, 2);
	while (a[i] != '\0')
	{
		write(2, &a[i], 1);
		i++;
	}
	write(2, "\n", 1);
	exit(exit_code);
}

size_t	where_is(char *arg, char needle)
{
	size_t	wc;
	int		i;

	wc = 0;
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == needle)
			wc++;
		i++;
	}
	return (wc);
}

void	command_check(char *arg)
{
	if ((ft_strlen(arg) == 0) || (where_is(arg, '/') == ft_strlen(arg)))
		err("permission denied: ", arg, 126);
	if (((where_is(arg, '.') == 1)))
		err("not enough arguments:", arg, 1);
	if (((where_is(arg, '.') == 2)))
		err("permission denied: ", arg, 126);
	if (where_is(arg, '.') == ft_strlen(arg))
		err("command not found: ", arg, 127);
	if (where_is(arg, ' ') == ft_strlen(arg))
		err("command not found: ", arg, 127);
}
