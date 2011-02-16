#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int fi,fo;
    char route[256] = "/home/yaomoon/study/main/aa";
    char buf[10] = "yaomingyue";
    char buf2[256] = {0};
    struct stat bus;
    FILE *dk;
    int i;

    stat(argv[1], &bus);
    fi = open(argv[1], O_RDWR, 0644);
    fo = open(argv[2], O_RDWR, 0644);

    while(read(fi, buf2, 10) > 0)
    {
        printf("%s",buf2);
        write(fo, buf2, 10);
    }
    close(fi);
    close(fo);

    /*
    dk = fopen("yao","w");
    for (i = 0; i < 100; i++) 
    {
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d\n",i);
        
    }
    fclose(dk);
    */

    return 0;
}
