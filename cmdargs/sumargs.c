#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	int num;
	int sum;
   if(argc > 3)
    {
        printf("Invalid command line: supply two integers \n");
        exit(1);
    }

	for(i=1; i<argc; i++){
	printf("argv[%d]=%s\n",i,argv[i]);		
	num=atoi(argv[i]);
	printf("int output of argv[%d]: %d\n",i,num);
	sum+=num;
}
	printf("the sum is: %d\n",sum);

	return 0;
}

