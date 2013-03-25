#include <stdio.h>
#include <string.h>
char *converse_str(char *src)
{
    int len = strlen(src);
    int i;
    char temp;

    for (i = 0; i < len/2; i++) 
    {
        temp = src[i];
        src[i] = src[len-1-i];
        src[len-i-1] = temp;
    }

    return src;

}

int main(int argc, const char *argv[])
{
    char kk[10] = "yaomoon";
    char *name;
    
    name = converse_str(kk);
    printf("name:%s\n",name);
    printf("name:%s\n",kk);
    return 0;
}
