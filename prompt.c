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
void prompt(char qw[])
{
        char hostname2[1024];
        hostname2[1023] = '\0';
        char hostname[1024];
        hostname[1023] = '\0';
        char hostname1[1024];
        hostname1[1023] = '\0';
        getcwd(hostname1,1023);
        gethostname(hostname, 1023);
        if(strlen(hostname1)>12)
        {
                int flag=0;
                for(int i=0;i<15;i++)
                {
                        if(qw[i]!=hostname1[i])
                        {
                                flag=1;
                                break;
                        }
                }
                int c=1;
                if(flag==0)
                {
                        while (c <= strlen(hostname1)-15) {
                                hostname2[c] = hostname1[15+c-1];
                                c++;
                        }
                        hostname2[0]='~';
                        hostname2[c] = '\0';
                }
        }
        else
        {

                getcwd(hostname2,1023);

        }
        printf("%s@%s:%s$ ", getenv("USER"),hostname,hostname2);
}

