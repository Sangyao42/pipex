/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:28:09 by sawang            #+#    #+#             */
/*   Updated: 2023/04/14 18:05:09 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	pipex(t_info info, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (perror("first fork"), 1);
	if (pid[0] == 0)
		child_process1(fd, info, argv, envp);
	pid[1] = fork();
	if (pid[1] == -1)
		return (perror("second fork"), 1);
	if (pid[1] == 0)
		child_process2(fd, info, argv, envp);
	return (parent_process(fd, pid[0], pid[1]));
}

int	main(int argc, char *argv[], char **envp)
{
	t_info	info;
	int		exit_code;

	if (argc != 5)
	{
		ft_putstr_fd("usage: ./pipex infile cmd1 cmd2 outfile\n", STDERR_FILENO);
		exit(1);
	}
	paths_init(&info);
	info.paths = get_paths(envp);
	exit_code = pipex(info, argv, envp);
	strings_free(info.paths);
	return (exit_code);
}
