#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 80
int main()
{
	int fd, n;
	char buf[MAX];

	fd = open("out.txt", O_RDWR | O_CREAT);
	if(fd < 0 ) {
		printf("Open failed\n");
		exit(0);
	}
	
	printf("File descriptor = [%d]\n", fd);
	n = read(0, buf, MAX);
	/*n = write(fd,"hello", strlen("hello\n"));
	printf("write returned [%d]\n", n);
	*/
	write(1,buf,n);
	write(fd,buf,n);
	close(fd);
	return 0;

}
