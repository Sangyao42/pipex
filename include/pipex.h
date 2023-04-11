/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:47:41 by sawang            #+#    #+#             */
/*   Updated: 2023/04/11 15:22:46 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_info
{
	char	**paths;
}				t_info;

/**
 * main logic for pipe() and fork() in pipex.c
*/
int		pipex(t_info info, char **argv, char **envp);

/**
 * child processes and parent process in processes.c
*/
void	child_process1(int fd[2], t_info info, char **argv, char **envp);
void	child_process2(int fd[2], t_info info, char **argv, char **envp);
int		parent_process(int fd[2], pid_t pid1, pid_t pid2);

/**
 * get the right cmd_path from envp for execve(),
 * check if the cmd_path is accessible beforehand
*/
void	paths_init(t_info *info);
char	**get_paths(char **environp);
char	*get_cmd_path(char **paths, const char *cmd_arg0);

/**
 * error handling and free functions
*/
void	one_string_free(char *string);
void	strings_free(char **strings);
void	error_and_exit(char *msg, \
	char **paths, char **cmd_args, char *cmd_path);

#endif

