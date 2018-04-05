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
void  redirect(char **argv,int count,int flag)
{
    int in,out,i;
    int  flag3=-1;
    int flag1=-1,flag4=-1;
    int re=0,flag2=0;
    for(i=1;i<count-1;i++)
    {
        if(strcmp(*(argv+i),"<")==0)
        {
            if(flag2==0)
            {
                re=i;
                flag2=1;
            }
            flag3=i;
            *(argv+i)=NULL;
        }
        else if(strcmp(*(argv+i),">>")==0)
        {
            if(flag2==0)
            {
                re=i;
                flag2=1;
            }
            flag4=i;
            *(argv+i)=NULL;
        }
        else if(strcmp(*(argv+i),">")==0)
        {
            if(flag2==0)
            {
                re=i;
                flag2=1;
            }
            flag1=i;
            *(argv+i)=NULL;
        }
    }
    int status;
    if(flag2!=0)
    {
        if(flag==1)
        {
            if(fork()==0)
             {
            if(flag4!=-1)
            {
                out=open(*(argv+flag4+1),O_APPEND | O_WRONLY | O_CREAT);
                chmod(*(argv+flag4+1),0777);
            }
            if(flag3!=-1)
                in = open(*(argv+flag3+1), O_RDONLY);
            if(flag1!=-1)
            {
                out = creat(*(argv+flag1+1), 0644);
            }
            if(flag3!=-1)
                dup2(in, 0);
            if(flag1!=-1||flag4!=-1)
                dup2(out, 1);
            if(flag3!=-1)
                close(in);
            if(flag1!=-1||flag4!=-1)
                close(out);
            //execvp(*(argv),argv);
            execute(argv,re+1,0);
        }
        else if(flag==1)
          wait(&status);
        }
        else
        {
            if(flag4!=-1)
            {
                out=open(*(argv+flag4+1),O_APPEND | O_WRONLY | O_CREAT);
                chmod(*(argv+flag4+1),0777);
            }
            if(flag3!=-1)
                in = open(*(argv+flag3+1), O_RDONLY);
            if(flag1!=-1||flag4!=-1)
                out = open(*(argv+flag1+1), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            if(flag3!=-1)
                dup2(in, 0);
            if(flag1!=-1||flag4!=-1)
                dup2(out, 1);
            if(flag3!=-1)
                close(in);
            if(flag1!=-1)
                close(out);
            execute((argv),re+1,0);
        }
    }
    else
    {

         // printf("%d %d No redirections\n",count,flag);
        execute(argv,count,flag);
    }
    return ;
}

