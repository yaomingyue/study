#include "main.h"


void fun(int a)
{
    wait();
    printf("child closed\n");
}
void main(void)
{
    struct sigaction newsig;

    int i;
    int pd;
    int pd1, pd2;
    pid_t parent_pid;
    char *arg[10];
    arg[0] = "hello";
    sigset_t s;

    sigemptyset(&s);
    //sigaddset(&s, SIGINT);
    sigprocmask(SIG_BLOCK, &s, NULL);

    pd = fork();
    if(pd < 0)
    {
        perror("fork");
        exit(1);
    }
    if(pd > 0)
    {
        //newsig.sa_handler = SIG_IGN;
        //newsig.sa_flags = 0;
        //sigemptyset(&newsig.sa_mask);
        //
        //sigaction(SIGINT, &newsig, NULL);

        while(1)
        {
            sleep(1);
            printf("parent \n");
        }
    }
    if(pd == 0)
    {
        for (i = 0; i < 5; i++) 
        {
            sleep(1);
            printf("child111111 \n");
        }
    }
}

