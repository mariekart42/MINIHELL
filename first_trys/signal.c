#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// function fo rsignal funcs
#include <signal.h>

// libs for readline
#include <readline/readline.h>
#include <readline/history.h>

// void (*signal(int sig, void (*func)(int)))(int)
// macro SIGINT gets created to end a running program -> ctr-c

// there are different signals:
// SIGHUP  1   /* Hangup the process */ 
// SIGINT  2   /* Interrupt the process */  -->> what we need
// SIGQUIT 3   /* Quit the process */ 
// SIGILL  4   /* Illegal instruction. */ 
// SIGTRAP 5   /* Trace trap. */ 
// SIGABRT 6   /* Abort. */

// function only gets called if the signal SIGINT gets send from somewhere
void signal_handler(int keypress)
{
	printf("signal SIGINT got called\n");
//    printf("Caught signal %d, ends running program\n", keypress);
   exit(1); // bash: returns 1 if ctr-c is used
}

int main()
{
	char *line = NULL;

	printf("sigint val before: %d\n", SIGINT);
	while(1)
	{
		printf("in while loop\n");
		sleep(1);
	}
}
