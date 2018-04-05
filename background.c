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
#include "functios.h"
int background(char **argv){

        pid_t pid;
        pid=fork();
        int status;
        //child process
        if(pid==0)
        {
                setpgid(0,0);
                int val=execvp(argv[0],argv);
                if(val==-1)
                {
                        perror("error");
                        exit(1);
                }
        }
        else if(pid<0)
        {
                perror("error");
                return pid;
        }
        else
        {
                printf("%d\n",pid);
                return pid;
                // wait(NULL);
        }

}

