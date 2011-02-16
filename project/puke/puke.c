#include "main.h"

static char type[4][5] = {"黑","红","梅","方"};
static int player[4][15] = {0};
int sum[55];

void print_puke(void)
{
    int i, j, kk = 54, m, num;

    for (i = 0; i < 2; i++) 
    {
        printf("%s",i == 0 ?"A:":"B:");
        for (j = 0; j < 14; j++) 
        {
            printf("%s",player[i][j]<53?type[(player[i][j]-1)/13]:"  王");
            if(player[i][j]<53)
            printf("%2d   ",player[i][j]%13==0?13:player[i][j]%13);
            else
            {
                printf("\b\b\b\b");
                printf("%s   ",player[i][j]%13==1?"大王":"小王");
            }
        }
        printf("\n");
    }
    for (i = 2; i < 4; i++) 
    {
        printf("%s",i == 2 ?"C:":"D:");
        for (j = 0; j < 13; j++) 
        {
            printf("%s",player[i][j]<53?type[(player[i][j]-1)/13]:"  王");
            if(player[i][j]<53)
            printf("%2d   ",player[i][j]%13==0?13:player[i][j]%13);
            else
            {
                printf("\b\b\b\b");
                printf("%s   ",player[i][j]%13==1?"大王":"小王");
            }

        }
        printf("\n");
    }
}
void deal_puke(void)
{
    int i, j, kk = 54, m, num;

    for (i = 0; i < 2; i++) 
    {
        for (j = 0; j < 14; j++) 
        {
             num = rand()%kk;
             player[i][j] = sum[num]; 
             for (m = num; m < kk-1; m++) 
             {
                sum[m] = sum[m+1];
             }
             kk--; 
        } 
     }
    for (i = 2; i < 4; i++) 
    {
        for (j = 0; j < 13; j++) 
        {
             num = rand()%kk;
             player[i][j] = sum[num]; 
             for (m = num; m < kk-1; m++) 
             {
                sum[m] = sum[m+1];
             }
             kk--; 
        } 
     }
    
}
