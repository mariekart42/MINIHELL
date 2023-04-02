#include <unistd.h>
int main()
{
	write(2, "in knudel.c\n", 10);
	return (0);
}