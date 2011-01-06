#include <stdio.h>
int main(int argc, const char *argv[])
{
    int i,j;
    int a = 100000000;
    //fb_point(2,3,0xffff);
    /*
    printf("\033[43;31m");   // 设置背景颜色 
    printf("\33[2J");   //清屏 
    printf("\33[9;8H");   //设置光标位置 
    //printf("\33[4m");//下划线
    
    printf("\033[?25h");   //显示光标 
    //printf("\033[8A");   //将光标上移8行 
    printf("hello\n");    
    while(1);
    */
    //printf("\033[31m\033[5m ####---->>\033[32m""hello\n\033[m");  
    
    while(1)
    {
        for (j = 0; j < 30; j++) 
        {
            printf("\33[2J");   //清屏 
            printf("\33[%d;8H",j);   //设置光标位置 
            printf("%s\n","姚明月");
            while(i--);
            i = a;
        }
    }
   
    return 0;
}
