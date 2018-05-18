#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char * argv[])
{
//pid_t ret;
int i, num,sum=0,fact=1;
//ret=fork();
//string to integer with atoi
	for(i=1;i<argc; i++){
		num=atoi(argv[1]);
	}
//start forking a child --> factorial of num
     if (fork() == 0) {
		for(i=1;i<=num; i++){
			fact*=i;		
		}
	printf("\n[ID = %d] Factorial of %d is %d\n",getpid(),num,fact);	
	}
//the parent but we are going to fork again from here
     else{
	//forking another child --> sum of num
		if(fork()==0){
	           for(i=1;i<=num;i++){
	             sum+=i;
	           }
	         printf("\n[ID = %d] sum of positive integers up to %d is %d\n",getpid(),num,sum);
                }
//the parent after the second child 
                else{
                    while(wait(NULL) >0) // wait for both child to terminate
                    ;
	            printf("\n[ID = %d] DONE\n",getpid()); 
                }
     }
return 0;
}
