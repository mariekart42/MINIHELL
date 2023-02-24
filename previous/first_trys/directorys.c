#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// libs for readline
#include <readline/readline.h>
#include <readline/history.h>

// getcwd() -> gives current path of working directory
//		char *getcwd(char *buffer, size_t size)

// chdir() -> changes the current working directory of the calling process to the directory specified in path
//		int chdir(const char *path)
int main()
{
	char buffer[100];

	printf("current path: %s\n", getcwd(buffer, 10));
	// if (!buffer)
	// 	printf("getcwd failed\n");
}