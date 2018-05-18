#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int ret = fork();
	if(ret ==0)
		execlp("ps","ps","-f",NULL); /*not "/bin/ps" */
	wait(NULL);
	printf("Process status completed. \n");
	return 0;
}
