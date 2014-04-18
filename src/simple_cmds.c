/*
 * simple_cmds.c
 *		This file contains the simple functions executed directly by the shell
 *
 *  Created on: 15/04/2014
 *      Author: seb
 */

#include "definers.h"
#include "call_prog.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Static global string to save to the environment variables */
static char env_string[MAXLEN]; 

/* External access to environment string array */
extern char** environ;

/*Clears the screen */
void clear() {
	system("clear");
}

/*Prints out given directory */
void dir(char** args) {
	char* list = "ls -al ";
	char* sent = malloc(strlen(list) + strlen(args[1]));

	strcpy(sent, list);
	strcat(sent, args[1]);

	system(sent); //CHANGE THIS FROM SYSTEM CALL TO FORK AND CALL
	free(sent);
}

/*Print environment variables*/
void print_env() {
	/*Uses external and accessible list of env variables */
	char** env = environ;

	while (*env) {
		printf("%s\n", *env++);
	}
}

/*Prints the current working directory*/
void pwd() {
	char* buf = malloc(MAXLEN);
	getcwd(buf, MAXLEN);
	printf("%s\n", buf);
	free(buf);
}

/*changes current working directory */
void change_directory(char ** args) {
	/* First, check the given path is a directory. Uses a stat() check to populate
	   the stat struct. */
	struct stat check;
	int exists = stat(args[1], &check); 
	if (exists == -1) {
		/* If it returns -1 and errno matches ENOENT variable, path doesn't exist */
		if (ENOENT == errno) {
			printf("%s does not exist.\n", args[1]);
			return;
		}
		else {
			perror("Stat check in cd function");
		}
	} else {
		/* If it does exist, check that it is a directory. Return if not */
		if (!S_ISDIR(check.st_mode)) {
			printf("%s is not a directory.\n", args[1]);
			return;
		}
	}
	
	chdir(args[1]); //changes current working directory

 	char* new_pwd = (char*) malloc(sizeof(char) * MAXLEN); //to save the new dir in

 	getcwd(new_pwd, MAXLEN); //re-retrieve the working directory to save as global

 	strcpy(env_string, "PWD="); //copy string into empty global. Must be global static because it cannot be deallocated after function returns
 	strcat(env_string, new_pwd); //then concatenate the new WD
 	putenv(env_string); //Put the new WD into env variables
 	printf("New working dir: %s\n", new_pwd);

 	free(new_pwd);
}
