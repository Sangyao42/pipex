/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:28:12 by sawang            #+#    #+#             */
/*   Updated: 2023/04/10 18:34:40 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../lib/Libft/libft.h"

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
	if (ft_strcmp(msg, "open") == 0)
	{
		perror("open");
		strings_free(paths);
		exit (1);
	}
	else if (ft_strcmp(msg, "execve") == 0)
	{
		perror("execve");
		strings_free(paths);
		strings_free(cmd_args);
		one_string_free(cmd_path);
		exit (errno);
	}

	perror("Unknown error");
	exit (1);
}
