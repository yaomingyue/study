#include "main.h"

int mycopy(const char *file1, const char *file2)
{
    int fi,fo;
    char buf[10] = "yaomingyue";
    char buf2[256] = {0};
    struct stat bus;
    FILE *dk;
    int i;

    stat(file1, &bus);
    fi = open(file1, O_RDWR, 0644);
    fo = open(file2, O_RDWR|O_CREAT, 0644);

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
        fprintf(dk, "%d\n",i);
        
    }
    fclose(dk);
    */

}
