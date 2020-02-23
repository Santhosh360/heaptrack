#include <stdio.h>
#include <stdlib.h>
int main()
{
	int *p[100];
	for(int i=0;i<100;i++){
		p[i]=(int *)malloc(100*sizeof(int));
	}
	for(int i=0;i<100;i++){
		free(p[i]);
	}
	return 0;
}
