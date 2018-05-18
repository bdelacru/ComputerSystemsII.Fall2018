#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * PrintHello(void * data)
{
    int my_data = (int)data;  
    sleep(1);
    printf("\n Hello from new thread - got %d !\n", my_data);
    //printf("\n Hello from new thread %u - got %d !\n", 
    pthread_exit(NULL);
}

int main()
{
    int rc; // variable, place holder

    pthread_t thread_id; //creating thread variable
   // thread_id = pthread_self();

    pthread_t tid; //creating thread variable
    tid = pthread_self();

    int t = 11;

   rc = pthread_create(&thread_id,NULL, PrintHello, (void*)tid); 

//creating thread 3 arg; first is the pointer to thread_id used by pthread_create to supply the thread's identifier, the second attributes for new thread - here is NULL to set default values, the third is has the new thread execute "PrintHello"
    //rc = pthread_create(pthread_self(), NULL, PrintHello, (void*)t);
    if(rc) // error
    {
      printf("\n ERROR: return code from pthread_create is %d \n", rc);
      exit(1);
    }
    //printf("\n Created new thread (%u)... \n", thread_id);
   printf("\n I am thread (%u). Created new thread (%u) .... \n", tid, thread_id);
    pthread_exit(NULL);//terminate
}

