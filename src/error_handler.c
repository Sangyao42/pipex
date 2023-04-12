/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:32:18 by sawang            #+#    #+#             */
/*   Updated: 2023/04/12 16:56:32 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	error_and_exit(char *msg, char **paths, char **cmd_args, char *cmd_path)
{
	if (ft_strncmp(msg, "command not found", 17) == 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		if (cmd_args)
			ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		strings_free(paths);
		strings_free(cmd_args);
		one_string_free(cmd_path);
		exit (127);
	}
	else if (msg)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(msg);
	}
	else
		perror("pipex");
	strings_free(paths);
	strings_free(cmd_args);
	one_string_free(cmd_path);
	exit (1);
}

// void	error_and_exit(char *msg, char **paths, char **cmd_args, char *cmd_path)
// {
// 	if (ft_strncmp(msg, "open", 4) == 0)
// 	{
// 		perror("open");
// 		strings_free(paths);
// 		exit (errno);
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
// 		if (cmd_args)
// 			ft_putstr_fd(cmd_args[0], STDERR_FILENO);
// 		ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 		strings_free(paths);
// 		strings_free(cmd_args);
// 		exit (127);
// 	}
// 	perror("Unknown error");
// 	exit (1);
// }

// void	error_and_exit(char *msg, char **paths, char **cmd_args, char *cmd_path)
// {
// 	// if (ft_strncmp(msg, "open", 4) == 0)
// 	// 	perror("open");
// 	// else if (ft_strncmp(msg, "execve", 6) == 0)
// 	// 	perror("execve");
// 	if (ft_strncmp(msg, "command not found", 17) == 0)
// 	{
// 		if (cmd_args)
// 			ft_putstr_fd(cmd_args[0], STDERR_FILENO);
// 		ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 		strings_free(paths);
// 		strings_free(cmd_args);
// 		one_string_free(cmd_path);
// 		exit (127);
// 	}
// 	else
// 		perror(msg);
// 	strings_free(paths);
// 	strings_free(cmd_args);
// 	one_string_free(cmd_path);
// 	exit (errno);
// }
