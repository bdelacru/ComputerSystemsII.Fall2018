#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void fork4()
{
	printf("\n [%d] L0 \n", getpid());
	fork();
	printf("\n [%d] L1 \n", getpid());
	fork();
	printf("\n [%d] Bye \n", getpid());
}

int main()
{
	fork4();
	return 0;
}
