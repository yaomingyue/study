#include "main.h"

void pipeline(void)
{
   int len;
   int fd[2];
   char buf[10] = {0};
   pid_t pid;
   int data[5];
   int i = 0;

   if(pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }
    if((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    if(pid == 0)
    {
        close(fd[0]);
        while(1)
        {
            sleep(1);
            sprintf(buf, "%4d", i);
            write(fd[1], buf, 4);
            i++;
        }
    }
    if(pid > 0)
    {
        close(fd[1]);
        while(1)
        {
            len = read(fd[0], buf, 4);
            printf("%s\n",buf);
            //write(STDOUT_FILENO, buf, len);
        }
        wait(NULL);
    }
}
