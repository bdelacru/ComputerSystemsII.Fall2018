#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd,ret= fork();
    char * cmd[] = {"ls","-l", NULL};
   
    if(ret == 0)
    {
	fd = open("out2.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); 
        //open(fname, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); 
	//file that are created with permissions 
        dup2(fd, 1);
        close(fd);
        printf("Redirected to file\n"); fflush(stdout);
	printf("Child has executed\n");
	execvp(cmd[0],cmd);
        
        exit(0);
    }
    wait(NULL);
    printf("Child doneeeeeee\n");
   return 0;
}
