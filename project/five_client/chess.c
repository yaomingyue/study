#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

char board[P_NUM*V_NUM] = {0};
u32_t color_choice = 0xffffffff;;
char who = 1;

int choose_color(int x, int y)
{
    if((y>=0) && (y<=85))
    {
        color_choice = 0x01000000;  
        who = 2;
    }
    else if((y>=85) && (y<=160))
    {
        color_choice =0xffffffff; 
        who = 1;
    }
    return 0;
}

int chess_print(int mx, int my)
{
    int x = mx;
    int y = my;
    int k;
    
    x = (x-START_X)/SPACE;
    y = (y-START_Y)/SPACE;
    if(((mx-START_X)%SPACE) > (SPACE/2))
        x++;
    if(((my-START_Y)%SPACE) > (SPACE/2))
        y++;
    if(board[x+y*V_NUM] == 0)
    {
        //if(x < START_X||x > (START_X+SPACE*(V_NUM-1))||y < START_Y||y >(START_Y+SPACE*(P_NUM-1)))
        //{
        //choose_color(mx,my);  
        //return 0;
        //}
        //else
        //{
            fb_circle(mx, my,10, color_choice);
            return 1;
            //}
    }
}

int fb_circle(int x0, int y0, int r, u32_t color)
{
   int dx = (x0-START_X)%30;
   int dy = (y0-START_Y)%30;
   x0 = (dx - 15 < 0)?x0-dx:x0+30-dx; 
   y0 = (dy - 15 < 0)?y0-dy:y0+30-dy; 
    int x = 0; 
    int y = r;

    int p = 3 - 2*r;
    while(x <= y)
    {
        fb_line(x0+x, y0+y, x0-x, y0+y, color);
        fb_line(x0+y, y0+x, x0-y, y0+x, color);
        fb_line(x0+y, y0-x, x0-y, y0-x, color);
        fb_line(x0+x, y0-y, x0-x, y0-y, color);
        
        if(p<0)
        {
            p += 4*x + 6;
        }
        else
        {
            p += 4*(x-y) + 10;
            y--;
        }
        x++;
    }
    return 0;

}

void check_won(int x0, int y0)
{
    int i, j;
    char storage = 0;
    char counter = 0;
    char nx = 0;
    char ny = 0;

    char n_x[4] = {0,1,1,1};
    char n_y[4] = {1,0,1,-1};
    int x = x0;
    int y = y0;
    int k;
    
    x = (x-START_X)/SPACE;
    y = (y-START_Y)/SPACE;
    if(((x0-START_X)%SPACE) > (SPACE/2))
        x++;
    if(((y0-START_Y)%SPACE) > (SPACE/2))
        y++;
    board[x+y*V_NUM] = who;
    storage = board[x+y*V_NUM];
    for (k = 0; k < 4; k++) 
    {
        for (i = 4; i >= 0 ; i--) 
        {
           nx = x - i*n_x[k];
           ny = y - i*n_y[k];
           if((board[nx+ny*V_NUM] == storage)&&(nx >= 0)) 
           {
                for (j = 0; j < 5; j++) 
                {
                   if((board[nx+ny*V_NUM] == storage)&&(nx <= V_NUM-1))
                        counter++;
                   else
                        break;
                    nx += n_x[k];
                    ny += n_y[k];
                }
                if(counter == 5)
                     printf("%s won\n",who==1?"white":"black");
                counter = 0;

           }
            
        }

    }
    
}

#if 0

int chess_count(int x, int y)
{
    int i = x;
    int j = y;

    i = (i-START_X)/SPACE;
    j = (j-START_Y)/SPACE;
    if(((x-START_X)%SPACE) > (SPACE/2))
    {
        i++;
    }
    if(((y-START_Y)%SPACE) > (SPACE/2))
    {
        j++;
    }
    board[i+j*V_NUM] = who;
    return 0;
}

int check_five(int x, int y)
{
    int i = 0;
    char counter = 0;
    char storage = 0;
    int j = 0;

    char nx = 0;
    char ny = 0;

    char n_x[4] = {0,1,1,1};
    char n_y[4] = {1,0,1,-1};

    storage = board[x+y*V_NUM];
    if(storage == 0)
    {
        return 0;
    }
    for(j = 0; j < 4; j++)
    {
    
        
        counter = 1;
        nx = x;
        ny = y;

        for (i = 1; i < 5; i++) 
        {
            nx += n_x[j];
            ny += n_y[j];
            if(board[nx+ny*V_NUM] == storage)
            {
                counter++;
            }
            else 
            {
                break;
            }

        }
        if(counter == 5)
        {
            return storage;
        }
    }
    return 0;

}
int check_all(void)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < P_NUM; i++) 
    {
        for (j = 0; j < V_NUM; j++) 
       {
            if(check_five(i, j) !=0)
            {
                printf("%d won\n",who);
                return 1;
            }
        }
    }
  return 0;
}
#endif





















