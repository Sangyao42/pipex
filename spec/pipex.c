/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:50:21 by sawang            #+#    #+#             */
/*   Updated: 2023/04/10 20:11:39 by sawang           ###   ########.fr       */
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

void	one_string_free(char *string)
{
	if (!string)
		return ;
	free(string);
	string = NULL;
}

void	strings_free(char **strings)
{
	char	**current;

	if (!strings)
		return ;
	current = strings;
	while (*current)
	{
		free(*current);
		*current = NULL;
		current++;
	}
	free(strings);
	strings = NULL;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		ret_val;

	i = 0;
	ret_val = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		ret_val = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (ret_val != 0)
			return (ret_val);
		else
			ret_val = 0;
		i++;
	}
	return (ret_val);
}

char	**get_paths(char **environ)
{
	int		i;
	char	**paths;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_split(*(environ + i) + 5, ':');
	return (paths);
}

char	*get_cmd_path(char **paths, const char *cmd_arg0)
{
	int		i;
	char	*temp_path;
	char	*cmd_path;

	if (ft_strnstr(cmd_arg0, "/", ft_strlen(cmd_arg0)) || \
		ft_strnstr(cmd_arg0, "$(which", ft_strlen(cmd_arg0)))
		return ((char *)cmd_arg0);
	i = -1;
	while (paths[++i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp_path, cmd_arg0);
		one_string_free(temp_path);
		if (access(cmd_path, F_OK & X_OK) == 0)
			return (cmd_path);
		one_string_free(cmd_path);
	}
	return (NULL);
}

// void	error_and_exit(char *msg, char **paths, char **cmd_args, char *cmd_path)
// {
// 	if (ft_strncmp(msg, "open", 4) == 0)
// 	{
// 		perror("open");
// 		strings_free(paths);
// 		exit (1);
// 	}
// 	else if (ft_strncmp(msg, "execve", 6) == 0)
// 	{
// 		perror("execve");
// 		strings_free(paths);
// 		strings_free(cmd_args);
// 		one_string_free(cmd_path);
// 		exit (errno);
// 	}
// 	else if (ft_strncmp(msg, "command not found", 17) == 0)
// 	{
// 		ft_putstr_fd("command not found: ", STDERR_FILENO);
// 		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 		strings_free(paths);
// 		strings_free(cmd_args);
// 		exit (127);
// 	}
// 	perror("Unknown error");
// 	exit (1);
// }

void	error_and_exit(char *msg, char **paths, char **cmd_args, char *cmd_path)
{
	// if (ft_strncmp(msg, "open", 4) == 0)
	// 	perror("open");
	// else if (ft_strncmp(msg, "execve", 6) == 0)
	// 	perror("execve");
	if (ft_strncmp(msg, "command not found", 17) == 0)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		perror(msg);
	strings_free(paths);
	strings_free(cmd_args);
	one_string_free(cmd_path);
	exit (errno);
}

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
	cmd_path = get_cmd_path(info.paths, cmd_args[0]);
	if (cmd_path)
	{
		execve(cmd_path, cmd_args, envp);
		error_and_exit("execve", info.paths, cmd_args, cmd_path);
	}
	errno = 127;
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
		error_and_exit(argv[4], info.paths, cmd_args, cmd_path);// error_and_exit("open"); free info.paths
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
		error_and_exit("execve", info.paths, cmd_args, cmd_path);
	}
	errno = 127;
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
		perror("unexpected exit from outside process");
		return (1);
	}
}

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
