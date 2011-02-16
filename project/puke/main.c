#include "main.h"
#include "puke.h"

int main(void)
{
    int i, kk = 54;

    srand(time(NULL));
    for (i = 0; i < kk; i++) 
    {
        sum[i] = i+1;
    }
    deal_puke();
    print_puke();
    printf("\n");
}


