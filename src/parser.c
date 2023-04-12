/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:34:40 by sawang            #+#    #+#             */
/*   Updated: 2023/04/12 22:33:24 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	paths_init(t_info *info)
{
	info->paths = NULL;
}

char	**get_paths(char **environp)
{
	int		i;
	char	**paths;

	i = 0;
	while (environp[i])
	{
		if (ft_strncmp(environp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_split(*(environp + i) + 5, ':');
	return (paths);
}

char	*get_cmd_path(char **paths, const char *cmd_arg0)
{
	int		i;
	char	*temp_path;
	char	*cmd_path;

	if (ft_strnstr(cmd_arg0, "/", ft_strlen(cmd_arg0)))
	{
		if (access(cmd_arg0, X_OK) == 0)
		{
			cmd_path = ft_strdup(cmd_arg0);
			return (cmd_path);
		}
	}
	i = -1;
	while (paths[++i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp_path, cmd_arg0);
		one_string_free(temp_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		one_string_free(cmd_path);
	}
	return (NULL);
}
