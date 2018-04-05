
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
sigjmp_buf env;
void exit_child(void)
{
        pid_t child;
        int status;
        while ((child = waitpid(-1, &status, WNOHANG)) > 0)
        {
                printf("\nChild with pid %d excited normally\n",child);
        }
        siglongjmp(env,1);
}

