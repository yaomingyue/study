#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    FILE *fp;
    char info[100] = {0};



    while(1)
    {
        sleep(1);
        fp = fopen("/sys/power/wake_lock","r");
        if(!fp)
        {
            printf("error:%d\n",errno);
        }

        memset(info,0,100); 
        fread(info,100,1,fp);
        printf("%s\n",info);
        fclose(fp);
    }

    return 0;
}
