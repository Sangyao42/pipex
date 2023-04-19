#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	printf("%s\n", *envp);
	printf("%p\n", envp);
	execve("test.sh", (char *[2]) {"jesus", 0}, envp);
	return 0;
}
