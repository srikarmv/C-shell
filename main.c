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
#include <sys/prctl.h>
#include <signal.h>
#include <setjmp.h>
#include "functios.h"
typedef struct proc
{
    char pname[200];
    pid_t pid;
    struct proc *next;
}proc;
char qw[1000];
sigjmp_buf env;
void allc(int pipeid[],int k)
{
    for(int i=0;i<k*2;i++)
        close(pipeid[i]);
}
proc *bgp;
sigjmp_buf env;
void insert(char name[],pid_t pid)
{
    proc *new=(proc *)malloc(sizeof(proc));
    strcpy(new->pname,name);
    new->pid=pid;
    new->next=NULL;
    if(bgp==NULL)
        bgp=new;
    else
    {
        proc *temp=bgp;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=new;
    }
}
void delete(pid_t pid)
{
    if(bgp!=NULL)
    {
        proc *temp=bgp;
        if(bgp->pid==pid)
        {
            bgp=bgp->next;
            free(temp);
        }
        else
        {
            proc *r; 
            while(temp!=NULL&&temp->pid!=pid)
            {
                r=temp;
                temp=temp->next;
            }
            if(temp!=NULL)
            {
                r->next=temp->next;
                free(temp);
            }
            else
                ;
        }
    }
}
void job()
{
    int count=0;
    proc *temp1=bgp;
    if(temp1==NULL)
        return;
    if(temp1->next==NULL)
        printf("[0] %s %d\n",temp1->pname,temp1->pid);        
    while(temp1->next!=NULL)
    {
        printf("[%d] %s %d\n",count,temp1->pname,temp1->pid);        
        count++;
        temp1=temp1->next;
        if(temp1->next==NULL)
        {
            printf("[%d] %s %d\n",count,temp1->pname,temp1->pid);
            count++;
        }
    }
    return;
}
void exit_child(void)
{
    pid_t child;
    int status;
    while ((child = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("\nChild with pid %d excited normally\n",child);
        delete(child);
    }
    siglongjmp(env,1);
}
void killall()
{
    proc *temp1=bgp;
    if(temp1==NULL)
        return;
    if(temp1->next==NULL)
    {
        kill(temp1->pid,9);
    }
    while(temp1->next!=NULL)
    {   
        kill(temp1->pid,9);
        temp1=temp1->next;
        if(temp1->next==NULL)
        {
            kill(temp1->pid,9);
        }
    }   
}
void kj(int j,int k)
{
    proc *temp1=bgp;
    int count=1;
    if(temp1==NULL)
        return;
    if(temp1->next==NULL)
    {
        if(j==1)
            killpg(temp1->pid,k);
    }
    while(temp1->next!=NULL)
    {
        if(j==count)
        {
            killpg(temp1->pid,k);
            return;
        }
        temp1=temp1->next;
        count++;
        if(temp1->next==NULL)
        {
            if(j==count)
            {
                killpg(temp1->pid,k);
                return;
            }
            count++;
        }
    }
    return ;
}
void fds(int j)
{
    proc *temp1=bgp;
    int count=1;
    int ans;
    if(temp1==NULL)
        return;
    if(temp1->next==NULL)
    {
        if(j==1)
        {
            ans=temp1->pid;
            delete(ans);
        }
    }
    while(temp1->next!=NULL)
    {
        if(j==count)
        {
            ans=temp1->pid;
            delete(ans);
            break;
        }
        temp1=temp1->next;
        count++;
        if(temp1->next==NULL)
        {
            if(j==count)
            {
                ans=temp1->pid;
                delete(ans);
                break;
            }
            count++;
        }
    }
    int status;
    waitpid(ans,&status,0);
}
void fuc()
{
printf("\n");
prompt(qw);
fflush(stdout);
}
int main()
{
    getcwd(qw,1023);
    while(1){
        char *args[1024];
        char *ar[1024];
        prompt(qw);
        //	printf("%s",getenv("PWD"));
        char *line;
        ssize_t bufsize=0;
        signal(SIGINT,fuc);
        if(getline(&line,&bufsize,stdin)==-1)
        {
            //perror("");
            printf("\n");
            exit(0);
        }
        line[strlen(line)-1]='\0';
        int count1=1;
        char *token1;
        const char s2[2]=";";
        ar[0]=strtok(line,s2);
        token1=ar[0];
        if(ar[0]==NULL)
        {
            perror("Give input");
            continue;
        }
        while(token1!=NULL)
        {
            token1=strtok(NULL,s2);
            if(token1!=NULL)
                ar[count1]=token1;
            count1++;
        }
        ar[count1-1]=NULL;
        //printf("%d*\n",count1);
        for(int j=0;j<count1-1;j++)
        {
            if(strcmp(ar[j],"quit")==0)
            {
                exit(0);
            }
            int count=1;
            char *token;
            const char s[2]=" ";
            args[0]=strtok(ar[j],s);
            token=args[0];
            if(args[0]==NULL)
            {
                perror("Give input");
                continue;
            }
            while(token!=NULL)
            {
                token=strtok(NULL,s);
                if(token!=NULL)
                    args[count]=token;
                count++;
            }
            args[count-1]=NULL;
            int count2=0,stack[1000];
            for(int po=0;po<count-1;po++)
            {
                if(strcmp(args[po],"|")==0)
                {
                    stack[count2]=po;
                    args[po]=NULL;
                    count2++;
                }
            }
            stack[count2]=count-1;
            //printf("%d\n",count);
            if(strcmp(args[count-2],"&")==0)
            {
                args[count-2]=NULL;
                int yu=background(args);
                insert(args[count-3],yu);
                struct sigaction sa;
                sigfillset(&sa.sa_mask);
                sa.sa_handler=(void *)exit_child;
                sa.sa_flags=0;
                sigaction(SIGCHLD,&sa,NULL);
                sigsetjmp(env,1);
            }
            else
            {
                int status;
                if(count2 == 1)
                {
                    // printf("er\n");
                    if(fork()==0)
                    {
                        int pipeid[2];
                        int pid;
                        pipe(pipeid);
                        pid=fork();
                        if(pid!=0)
                        {
                            dup2(pipeid[0],0);
                            close(pipeid[0]);
                            close(pipeid[1]);
                            redirect((args+stack[0]+1),count-stack[0]-1,0);
                        }
                        else
                        {
                            dup2(pipeid[1],1);
                            close(pipeid[0]);
                            close(pipeid[1]);
                            redirect(args,stack[0]+1,0);
                        }
                    }
                    else
                        wait(&status);
                }
                else if(count2>1)
                {
                    if(fork()==0)
                    {
                        int pipeid[2*count2];
                        for(int p1=1;p1<=count2;p1++)
                            pipe(pipeid+(2*p1)-2);
                        for(int p1=0;p1<=count2;p1++)
                        {
                            if(fork()==0)
                            {
                                if(p1==0)
                                {
                                    dup2(pipeid[1],1);
                                    allc(pipeid,count2);
                                    redirect(args,stack[p1]+1,0);
                                }
                                else if(p1==count2)
                                {
                                    dup2(pipeid[(count2*2)-2],0);
                                    allc(pipeid,count2);
                                    redirect((args+stack[p1-1]+1),count-stack[p1-1]-1,0);
                                }
                                else
                                {
                                    dup2(pipeid[p1*2-2],0);
                                    dup2(pipeid[p1*2+1],1);
                                    allc(pipeid,count2);
                                    redirect((args+stack[p1-1]+1),stack[p1]-stack[p1-1],0);
                                }
                            }
                        }
                        allc(pipeid,count2);
                        for(int p1=0;p1<(2*count2)-1;p1++)
                            wait(&status);
                    }
                    else
                        wait(&status);
                }
                else
                {
                    if(strcmp(args[0],"fg")==0)
                    {
                        int yr=(int)(args[1][0])-'0';
                        fds(yr);
                    }
                    if(strcmp(args[0],"jobs")==0)
                        job();
                    else if(strcmp(args[0],"killallbg")==0)
                        killall();
                    else if(strcmp(args[0],"kjobs")==0)
                    {
                        int yr=(int)(args[1][0])-'0';
                        int er=(int)(args[2][0])-'0';
                        kj(yr,er);
                    }
                    else
                        redirect(args,count,1);
                }
            }
        }

    }
    return 0;
}
