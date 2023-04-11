/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:29:04 by sawang            #+#    #+#             */
/*   Updated: 2023/04/11 18:48:29 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(int fd[2], t_info info, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	int		fd_infile;

	cmd_args = NULL;
	cmd_path = NULL;
	fd_infile = open(argv[1], O_RDONLY, 0644);
	if (fd_infile == -1)
		error_and_exit(argv[1], info.paths, cmd_args, cmd_path);// error_and_exit("open"); free info.paths
	close(fd[0]);
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd_infile);
	cmd_args = ft_split(argv[2], ' ');
	if (cmd_args == NULL || cmd_args[0] == NULL)
		error_and_exit("command not found", info.paths, cmd_args, cmd_path);
	cmd_path = get_cmd_path(info.paths, cmd_args[0]);
	if (cmd_path)
	{
		execve(cmd_path, cmd_args, envp);
		error_and_exit("execve", info.paths, cmd_args, cmd_path);
	}
	// errno = 127;
	error_and_exit("command not found", info.paths, cmd_args, cmd_path);
}

void	child_process2(int fd[2], t_info info, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	int		fd_outfile;

	cmd_args = NULL;
	cmd_path = NULL;
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		error_and_exit(argv[4], info.paths, cmd_args, cmd_path);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd_outfile);
	cmd_args = ft_split(argv[3], ' ');
	// ft_putstr_fd(cmd_args[0], STDERR_FILENO);
	if (cmd_args == NULL || cmd_args[0] == NULL)
		error_and_exit("command not found", info.paths, cmd_args, cmd_path);
	cmd_path = get_cmd_path(info.paths, cmd_args[0]);
	if (cmd_path)
	{
		execve(cmd_path, cmd_args, envp);
		error_and_exit("execve", info.paths, cmd_args, cmd_path);
	}
	// errno = 127;
	error_and_exit("command not found", info.paths, cmd_args, cmd_path);
}

int	parent_process(int fd[2], pid_t pid1, pid_t pid2)
{
	int	wstats1;
	int	wstats2;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &wstats1, 0);
	waitpid(pid2, &wstats2, 0);
	if (WIFEXITED(wstats2))
		return (WEXITSTATUS(wstats2));
	else
	{
		// error_and_exit("unexpected exit from outside process");
		printf("error code:%d\t%d", WIFEXITED(wstats2), WEXITSTATUS(wstats2));
		perror("unexpected exit from outside process");
		return (1);
	}
}
