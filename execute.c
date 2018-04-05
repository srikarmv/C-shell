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
/*void exit_child(void)
  {
  pid_t child;
  int status;
  while ((child = waitpid(-1, &status, WNOHANG)) > 0)
  {
  printf("\nChild with pid %d excited normally\n",child);
  po=1;
  }
  siglongjmp(env,1);
//    exit(0);
return;
}*/
void  execute(char **argv,int count,int flag)
{
    if(flag!=1)
    {
/*        if(count>=3)
        {
            if(strcmp(argv[count-2],"&")==0)
            {
                argv[count-2]=NULL;
                background(argv);
                struct sigaction sa;
                sigfillset(&sa.sa_mask);
                sa.sa_handler=(void *)exit_child;
                sa.sa_flags=0;
                sigaction(SIGCHLD,&sa,NULL);
                sigsetjmp(env,1);
                exit(0);
            }
        }*/
        if(strcmp(argv[0],"cd")==0)
        {
            cd(argv);
            exit(1);
        }
        else if(strcmp(argv[0],"echo")==0)
        {
            echo(argv,count-1);
            exit(1);
        }
        else if(strcmp(argv[0],"pwd")==0)
        {
            char hostname3[1024];
            hostname3[1023] = '\0';
            getcwd(hostname3,1023);
            printf("%s\n",hostname3);
            exit(1);
        }           
        else
            execvp(*argv,argv);
    }
    else
    {
      /*  if(count>=3)
        {
            if(strcmp(argv[count-2],"&")==0)
            {
                argv[count-2]=NULL;
                background(argv);
                struct sigaction sa;
                sigfillset(&sa.sa_mask);
                sa.sa_handler=(void *)exit_child;
                sa.sa_flags=0;
                sigaction(SIGCHLD,&sa,NULL);
                sigsetjmp(env,1);
            }
        }*/
        if(strcmp(argv[0],"cd")==0)
        {
            cd(argv);
        }
        else if(strcmp(argv[0],"echo")==0)
        {
            echo(argv,count-1);
        }
        else if(strcmp(argv[0],"pwd")==0)
        {
            char hostname3[1024];
            hostname3[1023] = '\0';
            getcwd(hostname3,1023);
            printf("%s\n",hostname3);
        }           
        else
        {
            pid_t  pid;
            pid = fork();
            int corpse;
            int wai;
            if ((pid ) < 0) {
                //      printf(" ERR\n");
                perror("Error in executing child process\n");
                exit(1);
            }
            else if (pid == 0) {
                if (execvp(*argv, argv) < 0) {
                    //printf("ERROR while executing the command\n");
                      perror("Error while executing the command\n");
                    exit(1);
                }
            }

            else {
                while ((corpse = wait(&wai)) != -1 && corpse != pid)


                {
                    ;
                }
            }
        }
    }
}

