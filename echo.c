#include "functios.h"
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/file.h>
#include<sys/wait.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <signal.h>
#include <setjmp.h>
void echo(char **args,int argc)
{


	if (argc > 1)
	{

		int j;
		for(j=0;args[1][j]!='\0';j++)
		{
			if(args[1][j]!='"')
				printf("%c",args[1][j]);

		}
		printf(" ");
	}
	int i;
	for (i = 2; i < argc; i++)
	{
		int j;
		for(j=0;args[i][j]!='\0';j++)
		{
			if(args[i][j]!='"')
				printf("%c",args[i][j]);

		}
		printf(" ");
	}

	printf("\n");
	return ;
}

