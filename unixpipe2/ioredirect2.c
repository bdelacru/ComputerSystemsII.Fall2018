#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int fd,ret= fork();
    char * cmd[] = {"ls","-l", NULL};
   
    if(ret == 0)
    {
	fd = open("out2.txt", O_RDWR | O_CREAT);
        dup2(fd,1);
        close(fd);
        execvp(cmd[0],cmd);
        exit(0);
    }
    wait(NULL);
    printf("Child done\n");
   return 0;
}

