#include <stdio.h>
#include <unistd.h>

struct test {

unsigned int a :1;
};

int main(int argc, const char *argv[])
{

    int i = 0;

    struct test kk;


    kk.a = 1;
    printf("%d\n",kk.a);

    return 0;
}
