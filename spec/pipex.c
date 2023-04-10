/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:50:21 by sawang            #+#    #+#             */
/*   Updated: 2023/04/10 15:09:24 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../lib/Libft/libft.h"

typedef struct s_info
{
	char	**paths;
	// int		infile;
	// int		outfile;
}				t_info;

void	paths_init(t_info *info)
{
	info->paths = NULL;
	// info->infile = 0;
	// info->outfile = 0;
}

char	*get_cmd_path(char **paths, char cmd_arg0)
{
	int		i;
	char	*temp_path;
	char	*cmd_path;

	i = -1;
	while (paths[++i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp_path, cmd_arg0);
		free(temp_path);
		if (access(cmd_path, F_OK & X_OK) == 0)
			return (cmd_path);
	}
	return (NULL);
}

int	child_process1(int fd[2], t_info info, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	int		fd_infile;

	fd_infile = open(argv[1], O_RDONLY, 0644);
	if (fd_infile == -1)
		{}// error_and_exit("open"); free info.paths
	close(fd[0]);
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd_infile);
	cmd_args = ft_split(argv[2], ' ');
	cmd_path = get_cmd_path(info.paths, cmd_args[0]);
	if (cmd_path)
	{
		execve(cmd_path, cmd_args, envp);
		//free cmd args and cmd path and info.paths
		perror("execve");
		return (errno);
	}
	// free cmd args and info.paths
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd_args[0], STDERR_FILENO);
	return (127);
}

int	child_process2(int fd[2], t_info info, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	int		fd_outfile;

	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		{}// error_and_exit("open"); free info.paths
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd_outfile);
	cmd_args = ft_split(argv[3], ' ');
	cmd_path = get_cmd_path(info.paths, cmd_args[0]);
	if (cmd_path)
	{
		execve(cmd_path, cmd_args, envp);
		//free cmd args and cmd path and info.paths
		perror("execve");
		return (errno);
	}
	// free cmd args and info.paths
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd_args[0], STDERR_FILENO);
	return (127);
}

int	parent_process(int fd[2], t_info info, pid_t pid1, pid_t pid2)
{
	int	wstats1;
	int	wstats2;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &wstats1, WNOHANG);
	waitpid(pid2, &wstats2, WNOHANG);
	if (WIFEXITED(wstats2))
		return (WEXITSTATUS(wstats2));
	else
		// error_and_exit("unexpected exit from outside process");
		return (1);
}

int	pipex(t_info info, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		{}// error_and_exit("pipe");
	pid[0] = fork();
	if (pid[0] == -1)
		{}// error_and_exit("fork");
	if (pid[0] == 0)
		child_process1(fd, info, argv, envp);
	pid[1] = fork();
	if (pid[1] == -1)
		{}// error_and_exit("fork");
	if (pid[1] == 0)
		child_process2(fd, info, argv, envp);
	return (parent_process(fd, info, pid[0], pid[1]));
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
	paths_init(&info);
	info.paths = get_paths(envp);
	if (info.paths == NULL)
	{
		//error_and_exit
		perror("ft_split error");
		exit(1);
	}
	exit_code = pipex(info, argv, envp);
	strings_free(info.paths); //in ft_split.c, check first whether paths is NULL
	info.paths = NULL;
	return (exit_code);
}
