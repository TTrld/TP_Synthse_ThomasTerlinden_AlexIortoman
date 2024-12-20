#include <stdio.h>
#include "string.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 128

int fd;
char buf[BUFSIZE];
ssize_t ret;

char Shellstart[BUFSIZE] = "$ ./enseash\n";
char Outputestline1[BUFSIZE] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
char Endshell[BUFSIZE] = "enseash %\n";
char command[BUFSIZE];


int main(int argc, char* argv[]) {
	
    write(STDOUT_FILENO, Shellstart, strlen(Shellstart));
    write(STDOUT_FILENO, Outputestline1, strlen(Outputestline1));
    
    while(1){
	ret = read(STDIN_FILENO,command,BUFSIZE);
	if (ret < 0){
		perror("unknown command");
		exit(EXIT_FAILURE);
	}
		
	if (ret > 0 && command[ret - 1] == '\n') {
		command[ret - 1] = '\0';
        }
        
        command[ret]='\0'; //To avoid segmentation fault
        
	if (strcmp(command ,"exit")==0){
		break;
	}
		
	pid_t pid = fork(); // child program to execute a shell command (transfer of execution) while the father runs. 
        if (pid < 0) {
            perror("Error : fork");
            exit(EXIT_FAILURE);
	}
	//Child
        if (pid == 0) {
            execlp(Command, Command, (char *)NULL); // execution of Command
	    perror("Command execution error");
            exit(EXIT_FAILURE);
        } 
	// Father waits for child
	else {
            wait(NULL);
            write(STDOUT_FILENO,Endshell,strlen(Endshell));
        }
				
   }
	return 0;
}
