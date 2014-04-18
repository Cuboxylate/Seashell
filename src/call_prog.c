#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void syserr(char* ); 

/*Reassembles the original input and gives it to system */
void call(char** args, int wait) {
	pid_t pid;            // process ID
   	//int rc;               // return code

   	pid = getpid();       // get our own pid
   	printf("Process ID before fork: %d\n", (int)pid);

   	switch (pid = fork()) {
      	case -1:
         	syserr("fork");
         	break;
      	case 0:             // execution in child process
         	printf("Process ID in child after fork: %d\n", pid);
         	execvp(args[0], args);
         	syserr("execl"); // error if return from exec
            break;
         default:
            if (wait) {
               /* Parent waits for child process, with no status info returned */
               waitpid(pid, NULL, WUNTRACED);
            }
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
