#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../lib/Libft/libft.h"

// extern char	**environ;

typedef struct s_info
{
	char	**paths;
	int		infile;
	int		outfile;
}				t_info;

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


void	init_cmds(t_info *info)
{
	info->paths = NULL;
	info->infile = 0;
	info->outfile = 0;
}

void	update_cmds(t_info *info, int argc, char **argv, char **envp)
{
	init_cmds(info);
	info->infile = open(argv[1], O_RDONLY, 0666);
	if (info->infile == -1)
	{
		perror("open file1 error");
		return ;
	}
	info->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (info->outfile == -1)
	{
		perror("open file2 error");
		return ;
	}
	info->paths = get_paths(envp);
}

// int	main(int argc, char **argv)
// {
// 	init_cmds();//init cmd struct to get valid cmd and fd from infile and outfile
// 	int fd[2];
// 	pid1 = pipe();
// 	child process 1
// 	child process 2
// }

int	child_process1(int fd[2], t_info info, char **argv, char **envp)
{
	char	**cmd;
	char	*temp_path;
	char	*final_path;
	int		i;

	close(info.outfile);
	close(fd[0]);
	dup2(info.infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	// execute_cmd(info, argv, envp);
	cmd = ft_split(argv[2], ' ');
	i = -1;
	while (info.paths[++i])
	{
		temp_path = ft_strjoin(info.paths[i], "/");
		final_path = ft_strjoin(temp_path, cmd[0]);
		free(temp_path);
		if (access(final_path, F_OK & X_OK) == 0)
		{
			execve(final_path, cmd, envp);
			perror("execve1 error");
			return (2);
		}
		free(final_path);
	}
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	return (127);
}

int	child_process2(int fd[2], t_info info, char **argv, char **envp)
{
	char	**cmd;
	char	*temp_path;
	char	*final_path;
	int		i;

	close(info.infile);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(info.outfile, STDOUT_FILENO);
	close(fd[0]);
	cmd = ft_split(argv[3], ' ');
	i = -1;
	while (info.paths[++i])
	{
		temp_path = ft_strjoin(info.paths[i], "/");
		final_path = ft_strjoin(temp_path, cmd[0]);
		free(temp_path);
		if (access(final_path, F_OK & X_OK) == 0)
		{
			execve(final_path, cmd, envp);
			perror("pipex");
			return (2);
		}
		free(final_path);
	}
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	return (127);
}

int	*child_process(int fd[2], t_info info, char **argv, int i, char **envp)
{
	// int	err_code;

	if (i == 0)
		child_process1(fd, info, argv, envp);
	else if (i == 1)
		child_process2(fd, info, argv, envp);
}

int	parent_process(int fd[2], t_info info, int pid1, int pid2)
{
	int	status1;
	int	status2;

	close(fd[0]);
	close(fd[1]);
	close(info.infile);
	close(info.outfile);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
}

int	pipex(t_info info, char **argv, char **envp)
{
	int		fd[2];
	int		pid[2];
	int		i;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			return (2);
		}
		if (pid[i] == 0)
			child_process(fd, info, argv, i, envp);
		i++;
	}
	return (parent_process(fd, info, pid[0], pid[1]));
}

int	main(int argc, char *argv[], char **envp)// init t_cmds
{
	t_info	info;

	if (argc != 5)
	{
		printf("usage: ./pipex infile cmd1 cmd2 outfile\n");
		return (1);
	}
	update_cmds(&info, argc, argv, envp);
	if (info.infile == -1 || info.outfile == -1 || !info.paths)
		return (1);
	// int	i = 0;
	// while (paths[i])
	// {
	// 	printf("%s\n", paths[i]);
	// 	i++;
	// }
	pipex(info, argv, envp);
	free(info.paths);
	info.paths = NULL;
	return (0);
}
