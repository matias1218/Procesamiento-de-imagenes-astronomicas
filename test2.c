#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int a = 10;
	int b = 6;
	int c = a/b;

	printf("%d\n",1+c );
	printf("%d\n", c);
	return 0;
}
