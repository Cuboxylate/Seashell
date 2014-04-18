/*
 * chooser.c
 *
 *  Created on: 15/04/2014
 *      Author: Sebastian Dunn
 *
 *  Chooses which function to run given the first argument of the shell.
 *
 */
 #include "simple_cmds.h"
 #include "call_prog.h"
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>

int choose_command(char** args, int wait) {
	/*execute clear*/
	if (!strcmp(args[0], "clr")){
		clear();
	}

	/*execute dir if a path is given */
	else if (!strcmp(args[0], "dir")){
		if (args[1]) {
			dir(args);
		}
		else {
			printf("Please supply a directory.\n");
		}
	}

	/*print the environment variables out */
	else if (!strcmp(args[0], "environ")) {
		print_env();
	}

	else if (!strcmp(args[0], "quit")){
		return -1; //flag to break the input loop
	}

	else if (!strcmp(args[0], "cd")) {
 	//printf("Cmd: %s\tstring: %s\n" , args[0], args[1]);
		if (args[1] == 0) {
			pwd();
		}
		else {
			change_directory(args);
		}
	}

	/*if none of the above, send to system */
	else {
		call(args, wait);
	}
	return 0;
}



