#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	if (access("test.sh", F_OK) == 0)
		printf("OK\n");
	else
		printf("KO\n");
}
