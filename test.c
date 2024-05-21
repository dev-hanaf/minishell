#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("%s\n", getenv("PWD"));
	return (0);
}
