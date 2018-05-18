/*
int main(int argc, char * argv[])
{
	int i;
	printf("argc = [%d]\n", argc);
	
	for (i=0; i < argc; i++)
		printf("[%s]\n", argv[i]);
	return 0;
}
*/
#include <stdio.h>
 int main( int argc, char * argv[] )
    {
        int i;
        printf("\nProgram name is %s\n", argv[0]);
        printf("Program arguments are: \n");
        for(i = 1; i < argc; i++)
            printf("\t %s starts with %c\n", argv[i], argv[i][0]);
        return 0;
    }
