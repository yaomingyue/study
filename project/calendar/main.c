#include <stdio.h>
long int f(int year, int month)
{
    if(month < 3) return year - 1;
    else return year;
}
long int g(int month)
{
    if(month < 3) return month + 13;
    else return month + 1;
}
long int n(int year, int month, int day)
{
    return 1461L*f(year, month)/4 + 153L*g(month)/5 + day;
}

int w(int year, int month, int day)
{
    return (int) ((n(year, month, day)%7 - 621049L%7 + 7)%7);
}

int date[12][6][7];
int day_tb1[][12] = {{31,28,31,30,31,30,31,31,30,31,30,31},
                    {31,29,31,30,31,30,31,31,30,31,30,31}};
int main(int argc, const char *argv[])
{
    int green = 32,red = 31;
    int sw, leap, i, j, k, wd, day;
    int year;
    char title[] = "SUN MON TUE WED THU FRI SAT";

    printf("Please input the year whose calendar you want to know: ");
    scanf("%d%*c",&year);
    sw = w(year, 1, 1);
    leap = year%4==0&&year%100||year%400==0;
    for (i = 0; i < 12; i++) 
        for (j = 0; j < 6; j++) 
            for (k = 0; k < 7; k++) 
                date[i][j][k] = 0;

    for (i = 0; i < 12; i++) 
        for (wd = 0,day=1;day<=day_tb1[leap][i];day++) 
        {
            date[i][wd][sw]=day;
            sw = ++sw%7;
            if(sw==0) wd++;
        }


    printf("\n|======================================="
    "the calendar of year  %d===================================|\n",year);
    for(i=0;i<4;i++)
    {
        printf("\033[32m \033[1m");
        for (wd=0,k=0;k<7;k++)
            wd+=date[i][5][k]+date[i+4][5][k]+date[i+8][5][k];
        wd=wd?6:5;
        printf("%2d  %s   %2d  %s   %2d  %s |\n",i+1,title,i+5,title,i+9,title);
        for (j = 0; j < wd; j++) 
        {
            printf("|");
            printf("  ");
            for (k = 0; k < 7; k++) 
                if(date[i][j][k])
                    printf("\033[1m\033[%dm%4d\033[m",k==0||k==6?red:green,date[i][j][k]);
                else printf("    ");

                printf("      ");
            for (k = 0; k < 7; k++) 
                if(date[i+6][j][k])
                    printf("\033[1m\033[%dm%4d\033[m",k==0||k==6?red:green,date[i+4][j][k]);
                else printf("    ");

                printf("      ");
            for (k = 0; k < 7; k++) 
                if(date[i+6][j][k])
                    printf("\033[1m\033[%dm%4d\033[m",k==0||k==6?red:green,date[i+8][j][k]);
                else printf("    ");
           
            printf("\033[32m\033[1m");
            printf("  |\n");

        }
    }
    printf("\033[m");
    puts("|====================================================================================================|");
    puts("\n press any key to quit...");
    getchar();
    return 0;
}












