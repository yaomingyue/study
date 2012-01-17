#include <stdio.h>

#define NUM 122
void printhello(void);
void myprint(void)
{
    printf("hello %d\n",NUM);
}

int main(int argc, const char *argv[])
{
    int a,b;
    
    printhello();

    myprint();

    return 0;
}
