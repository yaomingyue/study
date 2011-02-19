#include"main.h"

void mmap_cp(const char *addr1, const char *addr2)
{
    int fi, fo, n, len, i;
    char buf[10];
    struct stat bus;
    char *pin, *pout;

    stat(addr1, &bus);
    len = bus.st_size;

    fo = open(addr2,O_RDWR|O_CREAT, 0644);
    fi = open(addr1,O_RDWR, 0644);
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
    
    pin = mmap(0, len, PROT_READ, MAP_SHARED, fi, 0); 
    pout = mmap(0, len, PROT_WRITE, MAP_SHARED, fo, 0); 
     
    for (i = 0; i < len; i++) 
    {
        *(pout + i) = *(pin + i);
    }

    close(fi);
    close(fo);
    
}

