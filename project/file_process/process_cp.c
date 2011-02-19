#include "main.h"

void process_cp(const char *addr1, const char *addr2, int pro_num)
{
    int fi, fo, fn, n, len, i, j;
    char buf[10];
    struct stat bus;
    char *pin, *pout;
    int *psize;
    int res;
    int size;

    stat(addr1, &bus);
    len = bus.st_size;

    fo = open(addr2,O_RDWR|O_CREAT, 0644);
    fi = open(addr1,O_RDWR, 0644);
    fn = open("cp_size",O_RDWR|O_CREAT, 0644);
    if(fi < 0 || fo < 0)
    {
        perror("open yao");
        exit(1);
    }

    //将要复制的目标文件扩展
    n = lseek(fo, len - 1, SEEK_SET);
    if(n < 0)
    {
        perror("failed");
    }
    write(fo, buf, 1); 
    n = lseek(fn, 4 - 1, SEEK_SET);
    if(n < 0)
    {
        perror("failed");
    }
    write(fn, buf, 1); 

    pin = mmap(0, len, PROT_READ, MAP_SHARED, fi, 0); 
    pout = mmap(0, len, PROT_WRITE, MAP_SHARED, fo, 0); 
    psize = mmap(0, 4, PROT_WRITE|PROT_READ, MAP_SHARED, fn, 0); 
    
    *psize = 0;

    for (i = 0; i < pro_num; i++) 
    {
        res = fork();
        if(res < 0)
        {
            printf("fork%d\n",i);
            exit(1);
        }
        if(res == 0)
        {
            for (j = i*len/pro_num; j < (i+1)*len/pro_num; j++) 
            {
                usleep(1);
                *(pout + j) = *(pin + j);
                *psize = *psize + 1;
            }
            exit(0);
        }
    }
    if(res > 0)
    {
        printf("copy progress:\n");
        write(STDOUT_FILENO, "--------------  0%", 18);
        while(1)
        {
            sleep(1);
            write(STDOUT_FILENO, "\b\b\b\b", 4);
            size = *psize*100/len;
            sprintf(buf,"%3d",size);
            write(STDOUT_FILENO, buf, 3);
            write(STDOUT_FILENO, "%", 1);
            if(*psize*100/len == 100)
            {
                printf("\n");
                printf("copy completed\n");
                break;
            }
        }
        wait();
    }

    close(fi);
    close(fo);
    close(fn);
}

