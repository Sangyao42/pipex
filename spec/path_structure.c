#include "../lib/Libft/libft.h"
#include <stdio.h>
// #include <stddef.h>

extern char	**environ;

typedef struct s_cmds
{
	char	*cmd[2];
	int		infile;
	int		outfile;
}				t_cmds;

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

int	main(void)// init t_cmds
{
	char	**paths;
	t_cmds	*cmds;

	paths = get_paths(environ);
	// int	i = 0;
	// while (paths[i])
	// {
	// 	printf("%s\n", paths[i]);
	// 	i++;
	// }
	cmds->cmd[0] = get_cmd(paths, argv[2]);
	cmds->cmd[1] = get_cmd(paths, argv[3]);


	free(paths);
	return (0);
}

int	main(int argc, char **argv)
{
	init_cmds();//init cmd struct to get valid cmd and fd from infile and outfile
	int fd[2];
	pid1 = pipe();
	child process 1
	child process 2
}
