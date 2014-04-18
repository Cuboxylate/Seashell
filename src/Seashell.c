/*
 ============================================================================
 Name        : Seashell.c
 Author      : Sebastian Dunn
 Version     :
 Description : Simple shell implementation for COMP3520 Semester 1 2014,
 	 	 	 	 University of Sydney.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "chooser.h"
#include "definers.h"

void send_to_system(char**);
void syserr(char* );     // error report and abort routine

int main(int argc, char const *argv[]){
	char input[MAXLEN];							//Buffer for input
	char * args[MAXARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer through args
    char prompt[MAXLEN];                    // shell prompt

 	/* keep reading input until "quit" command or eof of redirected input */
	while (!feof(stdin)) {
		/*Get working directory, save into prompt print it at the input line*/
		getcwd(prompt, MAXLEN);
		strcat(prompt, " ==> ");
		fputs (prompt, stdout);

		/*save a line, and if it isn't null: */
		if (fgets(input, MAXLEN, stdin)) {
			arg = args; //point to first space in args
            *arg++ = strtok(input,SEPARATORS);   // first string tokenised and saved

            /* loops until end of input, saving each argument in args */
            while ((*arg++ = strtok(NULL,SEPARATORS)));
		}
		/* If the command isn't null: */
		if (args[0]) {
			int flag = choose_command(args);
			if (flag == -1) {
				send_to_system(args);
			}
		}
	}
	return 0;
}

/*Reassembles the original input and gives it to system */
void send_to_system(char** args) {
	pid_t pid;            // process ID
   	//int rc;               // return code

   	pid = getpid();       // get our own pid
   	printf("Process ID before fork: %d\n", (int)pid);

   	switch (fork()) {
      	case -1:
         	syserr("fork");
         	break;
      	case 0:             // execution in child process
         	pid = getpid();  // get child pid
         	printf("Process ID in child after fork: %d\n", pid);
         	execvp(args[0], args);
         	syserr("execl"); // error if return from exec
   	}

// continued execution in parent process

   pid = getpid();        // reget our pid
   printf("Process ID in parent after fork: %d\n", pid);
}

void syserr(char * msg)   // report error code and abort
{
   fprintf(stderr,"%s: %s", strerror(errno), msg);
   abort();
}

