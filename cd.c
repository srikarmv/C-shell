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
void cd(char **args)
{
    if(args[1]==NULL)
        return;
    if(args[1]=="~")
        chdir("/home/krishnav1");
    char cwd[1024];
    const char s1[2]="/";
    cwd[1023]='\0';
    char er[1024];
    er[1023]='\0';
    getcwd(er,1023);
    strcpy(cwd,er);
    strcat(cwd,s1);
    strcat(cwd,args[1]);
    if(chdir(args[1])==-1)
        perror("Not a excepted one");
    return;
}

