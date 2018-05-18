#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void fork6()
{
	printf("\n [%d] L0 \n", getpid());
	if (fork() == 0)
	{
		printf("\n [%d] L1 \n", getpid());
		if(fork() ==0)
	{
		printf("\n [%d] L2 \n", getpid());
		fork();
	}
	}
	printf("n [%d] Bye \n", getpid());
}

int main()
{
	fork6();
	return 0;
}
