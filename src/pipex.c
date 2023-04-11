/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:28:09 by sawang            #+#    #+#             */
/*   Updated: 2023/04/11 18:48:17 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(t_info info, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);// error_and_exit("pipe");
	pid[0] = fork();
	if (pid[0] == -1)
		return (perror("first fork"), 1);// error_and_exit("fork");
	if (pid[0] == 0)
		child_process1(fd, info, argv, envp);
	pid[1] = fork();
	if (pid[1] == -1)
		return (perror("second fork"), 1);// error_and_exit("fork");
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
		ft_putstr_fd("usage: ./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
		exit(1);
	}
	// if (envp == NULL)
	// {
	// 	// ft_putstr_fd("envp is NULL", STDERR_FILENO);
	// 	exit(1);
	// }
	paths_init(&info);
	info.paths = get_paths(envp);
	if (info.paths == NULL)
	{
		//error_and_exit
		// perror("ft_split error");
		// exit(1);
		return (perror("ft_split error"), 1);
	}
	exit_code = pipex(info, argv, envp);
	strings_free(info.paths); //in ft_split.c, check first whether paths is NULL
	// system("leaks pipex");
	// memory leaks tests needed
	return (exit_code);
}
