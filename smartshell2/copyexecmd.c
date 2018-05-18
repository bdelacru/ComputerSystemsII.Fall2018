
//----------------------------
// Name: Your Name Here
// Date: Spring 2018
// Class: Computer Systems II
// Assignment: Smart Shell
//----------------------------
 
#include <string.h>    /* for strcpy and strtok */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

 
/* Include other header files that are needed */
 
#define MAX_ARGV  10 /* maximum number of command tokens */
#define MAX_CMD   80 /* maximum length of command */
#define MAX 80       /* maximum number of buf */
 
void tokenize_cmd (char * cmd, int max, char * argv[])
/* Input:  cmd is the command to be tokenized
 *         max is the maximum number of tokens allowed  
 * Output: argv is the array of tokens (command arguments) 
 */
{
    int num_args = 0;           /* number of arguments (tokens) in cmd */
 
    if(cmd == NULL) return;     /* nothing to do */
 
    /* Tokenize the command */
    argv[0] = strtok(cmd, " \n");
    while((num_args < max) && (argv[num_args] != NULL))
    {
       num_args++;
       argv[num_args] = strtok(NULL, " \n");
    }
}
 
void execute_cmd(char * cmd)
{
    char * argv[MAX_ARGV];  /* array of command arguments*/ //10
    char cmd_copy[MAX_CMD]; /* buffer to store local copy of cmd*/ //80
 
    /* Make a local copy of the command */
    if(cmd == NULL) return; /* nothing to do */
    strcpy(cmd_copy, cmd);
 
    /* Tokenize the command */
    tokenize_cmd(cmd_copy, MAX_ARGV, argv);
    
    // Fork a child to execute the command 
    int ret = fork();
 // - if execvp fails, print an error message and exit
    if(ret<0){
	printf("Fork failed!\n");
	return;
	}
    else if(ret == 0){
	//execture command
       execvp(argv[0],argv);
	printf("Exec error \n");
	exit(0);
	}
 /* Parent waits for child to finish execution */
    else{
	wait(NULL);
	printf("DONE!\n");
    	//exit(0);
	}
    

}
 
int main()
{
char buf[MAX];
int input;
    /* Step 1:
     *   Add calls to execute_cmd here to test it out. 
     *   Example: execute_cmd("ps -f");
     *   ... other commands you wish to try here ...
     */
execute_cmd("ps -f");
printf("\n");
execute_cmd("mkdir aaa");
printf("\n");
execute_cmd("ls -l");
printf("\n");
execute_cmd("rm -r aaa");
printf("\n");
execute_cmd("ls -l");

    /*
     * Step 2: 
     *   Add code for your smart shell
     *   Read and process commands in an infinite loop
     *   Exit when the user types "quit" 
     */
     printf("myShell$ ");
   switch(fgets(buf,80,stdin)) {
 //fgets wait for input until the enter key is pressed. 
 //Everything is stored in buf up to 80 characters then goes on
 //num 0 value return so this creates an infinite loop 
   
   //printf("userInput:%s\n",buf);
   printf("myShell$:%s\n",buf);
    case "free":
   // when the user types free
	  if (strncmp(buf,"free",strlen("free"))==0){
	    execute_cmd("free");
	  }
	  else(strncmp(buf,"free -m -t",strlen("free -m -t"))==0){
	    execute_cmd("free -m -t");
	  }
/*
  //when the user types disk
    case "disk":
          if (strncmp(buf,"disk",strlen("disk"))==0){
             execute_cmd("df -h /dev/sda1");
             execute_cmd("df");
          }
  // when the user types quit
	   if (strncmp(buf, "quit", 4) == 0 ){
	      printf("breakking...\n");
		break;
	   }
          else{
               execute_cmd(buf);
		}
*/
  }
    // printf("\nProgram Quit...\n");
     return 0;
}
