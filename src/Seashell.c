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
#include "call_prog.h"

int main(int argc, char const *argv[]){
	char input[MAXLEN];							//Buffer for input
	char ** args;  // pointers to arg strings
    char ** arg;                               // working pointer through args
    char prompt[MAXLEN];                    // shell prompt

    /* Allocate space for the inputted argument array */
    args = (char**) malloc(sizeof(char*) * MAXARGS);


 	/* keep reading input until "quit" command or eof of redirected input */
	while (!feof(stdin)) {
		/*Get working directory, save into prompt print it at the input line*/
		getcwd(prompt, MAXLEN);
		strcat(prompt, " ==> ");
		fputs (prompt, stdout);
		int num_args;
		int wait;	//Int representation of bool, of whether a parent process should wait for child to finish.
					// Should be 0 is last arg is "&"

		/*save a line, and if it isn't null: */
		if (fgets(input, MAXLEN, stdin)) {
			arg = args; //point to first space in args
            *arg++ = strtok(input,SEPARATORS);   // first string tokenised and saved
            num_args = 1;
            /* If the first argument isn't just null, indicating the user pressed enter */
            if (args[0]) { 
		        /* loops until end of input, saving each argument in args and keeping track of num_args */
		        while (*arg++ = strtok(NULL,SEPARATORS)) { 
		        	num_args++; 
		        }

		        /* Check if the last arg is "&". If it is, flag not to wait for child processes */
				if (strcmp("&", args[num_args - 1]) == 0) {
					wait = 0;
					/* Set the & to null so it doean't interfere with external call */
					args[num_args - 1] = 0; 
				} else {
					/* No "&" means wait for child processes to finish */
					wait = 1; 
				}

				int flag = choose_command(args, wait);
				if (flag == -1) {
					/* -1 is returned if quit is called. Break while loop so memory is freed */
					break; 
				}
			}
		}
		
	}

	/* Free the input arg array */
    free(args);
	
	return 0;
}


