#include "nethelp.h"
/* Invoked with ./xechoclient localhost port */
int main(int argc, char * argv[])
{
 char buf[MAXLINE];

 if(argc < 2)
	{
	  printf("Invoke with %s port\n", argv[0]); 
	  exit(1);
	}
  char * hostname = argv[1];
  int port = atoi(argv[2]);

  int clientfd = open_clientfd(hostname, port); 
 //Test the connection
  while(fgets(buf, MAXLINE, stdin) != NULL)
 {
  write(clientfd, buf, strlen(buf));
  write(1, buf, strlen(buf));
  int n = read(clientfd, buf, MAXLINE);
  write(1, buf, n);
 }
 close(clientfd);
  return 0;

}
