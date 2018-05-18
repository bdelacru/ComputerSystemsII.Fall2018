#include <stdlib.h>
#include <stdio.h>
/*
int main( int argc, char *argv[] )
{

 	int num=atoi("356");
	printf("Test output: %d\n",num);
	return 0;
}
*/
int main(int argc, char *argv[])
{
	int i;
	int num;

	for(i=1; i<argc; i++){
	printf("argv[%d]=%s\n",i,argv[i]);		
	num=atoi(argv[i]);
	printf("int output of argv[%d]: %d\n",i,num);
}
/*
	for(i=1; i<argc; i++){
	printf("test output: %d\n",num);
	}*/
	return 0;
}

