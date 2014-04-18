/*
 * cd.c
 *
 *  Created on: 15/04/2014
 *      Author: seb
 */

#include "definers.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

	system(sent);
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
	chdir(args[1]); //changes current working directory

 	char* new_pwd = (char*) malloc(sizeof(char) * MAXLEN); //to save the new dir in

 	getcwd(new_pwd, MAXLEN); //re-retrieve the working directory to save as global

 	strcpy(env_string, "PWD="); //copy string into empty global. Must be global static because it cannot be deallocated after function returns
 	strcat(env_string, new_pwd); //then concatenate the new WD
 	putenv(env_string); //Put the new WD into env variables
 	printf("New working dir: %s\n", new_pwd);

 	free(new_pwd);
}
