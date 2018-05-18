
//----------------------------
// Name: Betsy De La Cruz
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
#include <fcntl.h>
#include <sys/stat.h>

 
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
 
void execute_output_redirect_cmd(char * cmd, char * fname)
{
	 char * argv[MAX_ARGV]; 
	 char cmd_copy[MAX_CMD];
	 int fd, ret=fork();
	 if(ret <0){ printf("Error\n"); return;}
	 //add code here
	 if(cmd == NULL) return;
	 strcpy(cmd_copy,cmd);
	tokenize_cmd(cmd_copy, MAX_ARGV, argv);
	if(ret ==0){
		fd = open(fname, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); 
		if(fd < 0 ) 
		{
			printf("Open failed\n");
			exit(0);
		}
		dup2(fd, 1);
		close(fd);
		execvp(argv[0],argv);
		printf("Exec error \n");
		exit(0);
	}
	 wait(NULL);
	 printf("Child done\n");

}
void execute_input_redirect_cmd(char *cmd, char *fname)
{
//add code here
	 char * argv[MAX_ARGV]; 
	 char cmd_copy[MAX_CMD];
	 int fd, ret=fork();
	 if(ret <0){ printf("Error\n"); return;}
	 //add code here
	 if(cmd == NULL) return;
	 strcpy(cmd_copy,cmd);
	tokenize_cmd(cmd_copy, MAX_ARGV, argv);
	if(ret ==0){
		fd = open(fname, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); 
		if(fd < 0 ) {
				printf("Open failed\n");
				exit(0);
		}
		dup2(fd, 0);
		close(fd);
		execvp(argv[0],argv);
		printf("Exec error \n");
		exit(0);
	}
	 wait(NULL);
	 printf("Child done\n");
}

void execute_piped_cmd(char * cmd1, char * cmd2){
 char * cmdargv1[MAX_ARGV]; 
 char * cmdargv2[MAX_ARGV]; 
 char cmd_copy1[MAX_CMD];
 char cmd_copy2[MAX_CMD];
 pid_t child_a,child_b;
 int mypipefd[2];
 int ret;
 if(cmd1 == NULL) return;
 if(cmd2 == NULL) return;
 strcpy(cmd_copy1,cmd1);
 strcpy(cmd_copy2,cmd2);
tokenize_cmd(cmd_copy1, MAX_ARGV, cmdargv1);
tokenize_cmd(cmd_copy2, MAX_ARGV, cmdargv2);
ret = pipe(mypipefd);
if(ret ==-1)
	{
		perror("pipe");
		exit(1);
	}

		child_a = fork();

		if (child_a == 0) {
		    // Child A code 
		    //closes the read end of the pipe and redirects the standard output to the write end of the pipe (using dup2). Then it calls execvp (with arguments taken cmdargv1) to execute the first command. With the standard output redirected to the pipe, the output of this command will go into the pipe.
		      printf("Child Process A:\npid :%d\nppid:%d\n",getpid(),getppid());
		      close(mypipefd[0]);// closes the read end of pipe
		      dup2(mypipefd[1],1); //redirects the stdout to the write end of the pipe
		      execvp(cmdargv1[0],cmdargv1); // execute the first command
		      printf("Exec error \n");
		      exit(0);
		} 
		else {
		    child_b = fork();

		    if (child_b == 0) {
			// Child B code 
		      printf("Child Process B:\npid :%d\nppid:%d\n",getpid(),getppid());
		      close(mypipefd[1]);// closes the write end of pipe
		      dup2(mypipefd[0],0); //redirects the stdin to the read end of the pipe
		      execvp(cmdargv2[0],cmdargv2);// execute the second command
		      printf("Exec error \n");
		      exit(0);
		    } else {
			// Parent Code 
		    printf("Parent Process:\npid :%d\nppid:%d\n",getpid(),getppid());
		    close(mypipefd[0]); //closes read end of pipe
		    close(mypipefd[1]); //closes write end of pipe
		    wait(NULL); //waits for Child A
		    wait(NULL);  //waits for Child B
	     
		 	}
		}
	
}
void process_cmd_line(char * cmd)
/* Parse the command line and check if it requires
input/output redirection or piped command execution,
then involke the appropriate execute function
*/
{
	char * p =cmd;
	char cmd_op =0;
	
	while(*p != '\0')
{
	if( (*p == '<') || (*p == '>') || (*p == '|'))
	{
		cmd_op = *p; // saves a copy of the command operator
		*p ='\0'; // mark the end of command to the left of special operator
		p++; // search for start of command to the right of special operator
		while(*p == ' ') p++;
		p[strlen(p)-1] = '\0'; //remove the newline character from the end of cmd
		break;
	}
	p++;
}
if(cmd_op == '|')
	execute_piped_cmd(cmd,p);
else if(cmd_op =='<')
	execute_input_redirect_cmd(cmd,p);
else if(cmd_op == '>')
	execute_output_redirect_cmd(cmd,p);
else
	execute_cmd(cmd);
}
int main()
{
char buf[MAX];
int input;

//code from past assignment 
/*	execute_cmd("ps -f");
	printf("\n");
	execute_cmd("mkdir aaa");
	printf("\n");
	execute_cmd("ls -l");
	printf("\n");
	execute_cmd("rm -r aaa");
	printf("\n");
	execute_cmd("ls -l");
*/
     //printf("myShell$ ");
   while( fgets(buf,MAX,stdin)) {
 //fgets wait for input until the enter key is pressed. 
 //Everything is stored in buf up to 80 characters then goes on
 //num 0 value return so this creates an infinite loop 
   //printf("myShell$ ");
   //printf("userInput:%s\n",buf);
   printf("myShell$:%s\n",buf);
   // when the user types free
	  if (strncmp(buf,"free",strlen("free"))==0){
	  // execute_cmd("free");     // if added, this becomes a dublicate
	  //else if(strncmp(buf,"free -m -t\0",strlen("free -m -t\0"))==0){
	    execute_cmd("free -m -t");
	  }
  //when the user types disk
          if (strncmp(buf,"disk",strlen("disk"))==0){
             execute_cmd("df -h /dev/sda1");
             execute_cmd("df");
          }
  // when the user types quit
	   if (strncmp(buf, "quit", 4) == 0 ){
	      printf(".........\n");
              printf(".......\n");
              printf(".....\n");
              printf("...\n");
		break;
	   }
          else{
              // execute_cmd(buf);
               process_cmd_line(buf);
		}
  }
     printf("\nProgram Quit...\n");
     return 0;
}
