#include "main.h" 

int read(int argc, const char *argv[])
{
    int fd, n;
    char buf[10];

    fd = open("yao",O_RDWR|O_CREAT);
    if(fd < 0)
    {
        perror("open yao");
        exit(1);
    }
    n = lseek(fd, 100, SEEK_END);
    if(n < 0)
    {
        perror("failed");
    }

    close(fd);
    
    return 0;
}
