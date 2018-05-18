/*
 * chatserver.c - A chat server
 * Communication protocol:
 *    JOIN name
 *    WHO
 *    LEAVE
 */

#include "nethelp.h"
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#define MAX_CLIENTS 100

typedef struct
{
   int fd;
   char * name;  
} client_info;

client_info clients[MAX_CLIENTS];  /* slot i is empty is clients[i].name = NULL */
sem_t mutex;  /* semaphore to protect critical sections */

/* Thread function */
void * HandleClient(void * arg);

/* Add client name in position index in the array 'clients' */
void HandleJOIN(char * name, int index);

/* Write the names of all active clients over the connection fd */
void HandleWHO(int fd);

/* Remove the client from position index in the array 'clients' */
void HandleLEAVE(int index);

/* Broadcast message from client in position index to all active clients */
void HandleBroadcast(char * msg, int index);

int main(int argc, char **argv) 
{
    int listenfd, port;
    struct sockaddr clientaddr;
    int clientlen = sizeof(struct sockaddr);
    int connfd, tid, i;

    if (argc != 2) {
	   fprintf(stderr, "usage: %s <port>\n", argv[0]);
	   exit(0);
    }
    /* Get the port number on which to listen for incoming requests from clients */
    port = atoi(argv[1]);

    for(i = 0; i < MAX_CLIENTS; i++)
       clients[i].name = NULL;

    /* Initialize semaphore to protect critical sections */
    sem_init(&mutex, 0, 1);

    /* Create a listening socket */
    listenfd = open_listenfd(port);

    while (1) {
       /* Accept an incoming request from a client */ 
	     connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
       if(connfd < 0) continue;  /* Connection failed */ 

       /* Allocate new entry in the array 'clients' for the new client 
        * Create a new thread to handle the client */
      sem_wait(&mutex);
       for(i = 0; i < MAX_CLIENTS; i++)
	{
	  if(clients[i].name == NULL)
           {
 		clients[i].fd = connfd;
                pthread_create(&tid, 0, HandleClient, (void*)i);
                break;
           }

	}
      sem_post(&mutex);

       /* 'clients' may be modified by other threads, protect with semaphore */
       
    }
}

/*
 * HandleClient - handle chat client
 * arg is the client index in the clients array
 */
void * HandleClient(void * arg) 
{
    size_t n; 
    char buf[MAXLINE];

    int index = (int)arg;  
    int connfd = clients[index].fd; 

    /* Detach the thread to free memory resources upon termination */
    pthread_detach(pthread_self());

    /* Read a line from the client (ended with '\0') */
    n = readline(connfd, buf, MAXLINE); 

    while(n > 0) {
       /* Process commands JOIN, WHO, LEAVE */
       /* Broadcast anything else */
       /* ADD CODE HERE */
       if(strncmp(buf, "JOIN", 4) == NULL)
          HandleJOIN(buf+4, index);
       if(strncmp(buf, "LEAVE", 5) == NULL)
          HandleLEAVE(index);

       /* Read the next line from the client (ended with '\0') */
       n = readline(connfd, buf, MAXLINE);
    }
    /* Close connection with client */
    close(connfd);
    return NULL;
}

/*
 * Send out client names in response to the WHO command
 */
void HandleWHO(int fd)
{
   /* ADD CODE HERE */
}

/*
 * Broadcast msg from client in position index to all active chat clients
 */
void HandleBroadcast(char * msg, int index)
{
   /* ADD CODE HERE */
}

/*
 * Add client name in position index in the array clients
 */
void HandleJOIN(char * name, int index)
{
    char buf[MAXLINE];
    int i;

    /* Make sure that client did not already join */
    sem_wait(&mutex);
    if(clients[index].name != NULL) {
       sprintf(buf, "Already joined as %s\n", clients[index].name);
       write(clients[index].fd, buf, strlen(buf));
       return;
    }
    

    /* Skip all the leading whitespaces */
    while((*name == ' ') || (*name == '\t')) name++;

    /* Replace '\n' by '\0' in user name */
    if(name[strlen(name)-1] == '\n') 
       name[strlen(name)-1] = '\0';
    clients[index].name = malloc(strlen(name)+1);
    strcpy(clients[index].name, name);

    for(i = 0; i < MAX_CLIENTS; i++)
	{
       if(clients[i].name == NULL) continue;
       if(i == index) 
          sprintf(buf, "Welcome to the chat room, %s!\n", name);
       else
          sprintf(buf, "%s has joined the chat room \n", name);
       write(clients[i].fd, buf, strlen(buf));
	}
    sem_post(&mutex);
}

/*
 * Remove client from position index in array cinfo
 * and close the connection to the client 
 */
void HandleLEAVE(int index)
{
   if(clients[index].name == NULL) return;
   free(clients[index].name);
   clients[index].name = NULL;
   close(clients[index].fd);
}









