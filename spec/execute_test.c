#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

extern char	**environ;

int	main(int argc, char **argv)
{
	int	fd_infile = open("testfile1.txt", O_RDONLY | O_CREAT, 0666);
	if (fd_infile == -1)
	{
		perror("open file1 error\n");
		return (1);
	}
	int	fd_outfile = open("testfile2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_outfile == -1)
	{
		perror("open file2 error\n");
		return (1);
	}
	int	fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	int pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid1 == 0)
	{
		close(fd_outfile);
		close(fd[0]);
		dup2(fd_infile, STDIN_FILENO);
		// dup2(fd[0], fd_infile);
		// printf("fd of fd_infile in pid1: %d\n", fd_infile);
		// printf("fd of read end of pid1: %d\n", fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		char*	vec[3] = { "grep", "hello", NULL };
		if (execve("/usr/bin/grep", vec, environ) == -1)
		{
			perror("execve error\n");
			return (2);
		}
	}
	int	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid2 == 0)
	{
		close(fd_infile);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		// dup2(fd[1], fd_outfile);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		char*	vec_wc[3] = { "wc", "-l" , NULL };
		if (execve("/usr/bin/wc", vec_wc, environ) == -1)
		{
			perror("execve");
			return (2);
		}
	}
	close(fd[1]);
	close(fd[0]);
	close(fd_infile);
	close(fd_outfile);
	int	wstats;
	waitpid(pid1, &wstats, 0);
	if (WIFEXITED(wstats))
	{
		if (WEXITSTATUS(wstats) == 2)
			printf("grep not found\n");
		else
			printf("grep exited successfully\n");
	}
	int	wstats2;
	waitpid(pid2, &wstats2, 0);
	if (WIFEXITED(wstats2))
	{
		if (WEXITSTATUS(wstats2) == 2)
			printf("wc not found\n");
		else
			printf("wc exited successfully\n");
	}

	return (0);
}


// int main(int argc, char* argv[]) {
//     int fd[2];
//     if (pipe(fd) == -1) {
//         return 1;
//     }

//     int pid1 = fork();
//     if (pid1 < 0) {
//         return 2;
//     }

//     if (pid1 == 0) {
//         // Child process 1 (ping)
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[0]);
//         close(fd[1]);
// 		return (0);
//         execlp("ping", "ping", "-c", "5", "google.com", NULL);
//     }

//     int pid2 = fork();
//     if (pid2 < 0) {
//         return 3;
//     }

//     if (pid2 == 0) {
//         // Child process 2 (grep)
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execlp("grep", "grep", "round-trip", NULL);
//     }

//     close(fd[0]);
//     close(fd[1]);

//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);

//     return 0;
// }
