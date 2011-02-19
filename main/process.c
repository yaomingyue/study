#include "main.h"

void process(void)
{
    int pd;
    int pd1, pd2;
    pid_t parent_pid;
    char *arg[10];
    arg[0] = "hello";

    pd = fork();
    if(pd < 0)
    {
        perror("fork");
        exit(1);
    }
    if(pd > 0)
    {
        pd1 = fork();
        if(pd1 < 0)
        {
            perror("fork parent");
            exit(1);
        }
        if(pd1 > 0)
        {
            while(1)
            {
                sleep(1);
                printf("parent \n");
                wait();
            }
        }
        if(pd1 == 0)
        {
            while(1)
            {
                sleep(3);
                printf("child22222\n");
                kill(getppid(), SIGKILL);
            }
        }
    }
    if(pd == 0)
    {
        pd2 = fork();
        if(pd2 < 0)
        {
            perror("fork parent");
            exit(1);
        }
        if(pd2 > 0)
        {
            while(1)
            {
                sleep(1);
                printf("child111111 \n");
            }
        }
        if(pd2 == 0)
        {
            execv("./hello", arg);
            sleep(1);
            printf("grandson\n");
            exit(1);
        }
    }
}

