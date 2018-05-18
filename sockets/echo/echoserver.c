		#include "nethelp.h"
 void * HandleClient(void *fd)
{
   int newfd= (int)fd;
   char buf[MAXLINE];

	printf("Before read\n");
        int n =  read(newfd, buf,MAXLINE);
	printf("After read n=%d\n", n);
      while(n>0)
      {
        write(1,buf, n);
        write(newfd, buf, n);
	n=read(newfd, buf,MAXLINE);
      }
}
/* Invoke with ./xechoserver port */

int main(int argc, char * argv[])
{
       char buf[MAXLINE];
       struct sockaddr clientaddr;
       int clientlen = sizeof(clientaddr);
       int tid;

	 if(argc < 2)
	{
	  printf("Invoke with %s port\n", argv[0]); 
	  exit(1);
	}

  int port = atoi(argv[1]);
  int listenfd = open_listenfd(port);
  if(listenfd < 0)
{
printf("Open listeining socket failed\n");
exit(1);
}

  while(1) //infinite loop 
  {
	int newfd = accept(listenfd, &clientaddr, &clientlen);
	if(newfd < 0)
	{
	   printf("Connection to client failed\n"); fflush(stdout);
           continue;
	}
        pthread_create(&tid, NULL, HandleClient,(void*)newfd);
       
  }
  return 0;

}
