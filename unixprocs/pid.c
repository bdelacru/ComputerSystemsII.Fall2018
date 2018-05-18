#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid, ppid;

	pid = getpid();
	ppid= getppid();

	printf("My identifier is [%d]\n", pid);
	printf("My parent's identifier is [%d]\n", ppid);

	while(1) ;

	return 0;

}
