#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int ret = fork();
	if(ret == 0)
		execl("/bin/ps", "ps","-f",NULL);
	wait(NULL);
	printf("Process status completed.\n");
	return 0;
}
