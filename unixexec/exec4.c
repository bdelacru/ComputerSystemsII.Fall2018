#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int ret;
	/* char * cmd[3] = {"ps","-f",NULL); */

	char *cmd[3];

	cmd[0] = "ps";		/* not "/bin/ps"*/
	cmd[1] = "-f";
	cmd[2] = NULL;

	ret = fork();
	if(ret == 0)
		execvp(cmd[0], cmd);
	wait(NULL);
	printf("Process status completed.\n");
	return 0;
}
