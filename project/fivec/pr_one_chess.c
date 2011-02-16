#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int prin_circle(int x0, int y0, int r, u32_t color)
{
    int x = 0; 
    int y = r;

    int p = 3 - 2*r;
    while(x <= y)
    {
        prin_line(x0+x, y0+y, x0-x, y0+y, color);
        prin_line(x0+y, y0+x, x0-y, y0+x, color);
        prin_line(x0+y, y0-x, x0-y, y0-x, color);
        prin_line(x0+x, y0-y, x0-x, y0-y, color);
        
        if(p<0)
        {
            p += 4*x +6;
        }
        else
        {
            p += 4*(x-y) +10;
            y--;
        }
        x++;
    }
    return 0;

}
void prin_one_chess(int x, int y)
{
    int dx = (x-START_X)%SPANCE;
    int dy = (y-START_Y)%SPANCE;

    x = (dx >= (SPANCE-1)/2)?(x+SPANCE-dx):(x-dx);
    y = (dy >= (SPANCE-1)/2)?(y+SPANCE-dy):(y-dy);
    prin_circle(x, y,CHESS_SIZE, 0x00ff0000);
    
}

