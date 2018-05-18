#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h>
int main ()
{int i;
for(i = 0; i < 2; ++i){
//start to fork Parent and child
  pid_t ret = fork();
//checking for failure
  if(ret < 0){
    printf("Fork Failed!\n");
    return 1;
  }
//Children 
  else if(ret == 0) {
    pid_t children_ret = fork();
     //checking for failure
    	if(children_ret < 0){
    	  printf("Fork Failed!\n");
     	  return 1;
         }
   //Grandchild 
	 else if(children_ret == 0) { 
           printf("\n [ID =%d] My parent is [%d]\n", getpid(), getppid());
           exit(0);
          }
    printf("\n [ID =%d] My parent is [%d]\n", getpid(), getppid());
    wait(NULL);
    exit(0);
  }
}
//Parent
printf("\n [ID = %d] I am the root parent \n", getpid());
wait(NULL);
exit(0);
return 0;
}
