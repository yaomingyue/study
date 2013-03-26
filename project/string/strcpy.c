#include <stdio.h>

char *my_strcpy(char *dest, const char *src)
{
    char *p = dest;

    if(dest == NULL||src == NULL)
        return NULL;
    while(*p++=*src++);

    return dest;
}

int main(int argc, const char *argv[])
{
    char kk[10] = "yaomoon";
    char name[10] = {0};

    my_strcpy(name, kk);

    printf("kk:%s\n",kk);
    printf("name:%s\n",kk);

    
    return 0;
}
