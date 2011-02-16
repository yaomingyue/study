#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num[10] = {0,1,2,3,4,5,6,7,8,9};
    int correct[5];
    int you_num[5];
    int a_num = 0, b_num = 0;
    int i, j, k;
    srand(time(NULL));

    for (i = 0; i < 4; i++) 
    {
        k = rand()%10;
        if(num[k] != 11)
        {
            correct[i] = num[k];
            num[k] = 11;
        }
        else 
        {
            i--;
        }
    }
    while(1)
    {
        printf("please input 4 number: ");
        scanf("%d %d %d %d",&you_num[0],&you_num[1],&you_num[2],&you_num[3]);

        for (i = 0; i < 4; i++) 
        {
            if(correct[i] == you_num[i])
            a_num++;
        }
        for (i = 0; i < 4; i++) 
        {
            for (j = 0; j < 4; j++) 
            {
                if(correct[i] == you_num[j])
                b_num++;
            }
        }
        b_num = b_num - a_num;
        printf("\n");
        printf("%dA %dB\n",a_num,b_num);
        if(a_num == 4)
        {
            printf("wonderful\n");
            break;
        }
        a_num = b_num = 0;
        
    }
   
    return 0;
}
