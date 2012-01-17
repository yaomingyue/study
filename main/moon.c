#include <stdio.h>

#define NUM 134

static void myprint(void)
{
    printf("hello moon %d\n",NUM);
}

void printhello(void)
{
    myprint();
}
