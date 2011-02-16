#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "main.h"

#define C_WIDTH 10
#define C_HEIGH 17
#define BORD 0x000000ff
#define X_ 0xffffffff
#define T_ 0x0

extern fb_info fb_infor;
static u32_t cursor_pixel[C_WIDTH*C_HEIGH]={
BORD,T_,T_,T_,T_,T_,T_,T_,T_,T_,
BORD,BORD,T_,T_,T_,T_,T_,T_,T_,T_,
BORD,X_,BORD,T_,T_,T_,T_,T_,T_,T_,
BORD,X_,X_,BORD,T_,T_,T_,T_,T_,T_,
BORD,X_,X_,X_,BORD,T_,T_,T_,T_,T_,
BORD,X_,X_,X_,X_,BORD,T_,T_,T_,T_,
BORD,X_,X_,X_,X_,X_,BORD,T_,T_,T_,
BORD,X_,X_,X_,X_,X_,X_,BORD,T_,T_,
BORD,X_,X_,X_,X_,X_,X_,X_,BORD,T_,
BORD,X_,X_,X_,X_,X_,X_,X_,X_,BORD,
BORD,X_,X_,X_,X_,X_,BORD,BORD,BORD,BORD,
BORD,X_,X_,BORD,X_,X_,BORD,T_,T_,T_,
BORD,X_,BORD,T_,BORD,X_,X_,BORD,T_,T_,
BORD,BORD,T_,T_,BORD,X_,X_,BORD,T_,T_,
T_,T_,T_,T_,T_,BORD,X_,X_,BORD,T_,
T_,T_,T_,T_,T_,BORD,X_,X_,BORD,T_,
T_,T_,T_,T_,T_,T_,BORD,BORD,T_,T_

}; 
static u32_t cursor_save[C_WIDTH*C_HEIGH];

void prin_cursor(int x, int y)
{
    int i, j;
    for (j = 0; j < C_HEIGH; j++) 
    {
        for (i = 0; i < C_WIDTH; i++) 
        {
            pr_one_pixel(x+i,j+y,cursor_pixel[i+j*C_WIDTH]);
        }
    }

}
void save_cursor(int x, int y)
{
    int *k = fb_infor.fbmem;
    int i, j;
    for (j = 0; j < C_HEIGH; j++) 
    {
        for (i = 0; i < C_WIDTH; i++) 
        {
          cursor_save[i+j*C_WIDTH] = k[x+i+(j+y)*fb_infor.w] ;
        }
    }
    
}
void report_cursor(int x, int y)
{
    int *k = fb_infor.fbmem;
    int i, j;
    for (j = 0; j < C_HEIGH; j++) 
    {
        for (i = 0; i < C_WIDTH; i++) 
        {
            k[x+i+(j+y)*fb_infor.w] = cursor_save[i+j*C_WIDTH];
        }
    }
}
int get_cursor_infor(int fd)
{
    
}

void doing()
{
    save_cursor(300,200);
    prin_cursor(300,200);
    sleep(2);
    report_cursor(300,200);
    prin_cursor(500,500);
}
void mosedoing()
{
    int fd;
    int mx = 512, my = 370;
    char buf[8];
    //prin_cursor(mx, my);
    int dx, dy, dz, button;
    fd = open("/dev/input/mice",O_RDWR);

    while(1)
    {
        read(fd,buf,8);
        button = buf[0]&0x07;
        dx = buf[1];
        dy = -buf[2];
        report_cursor(mx,my);
        mx += dx;
        my += dy;
        mx = mx>0?mx:0;
        my = my>0?my:0;
        mx = mx<(fb_infor.w-C_WIDTH)?mx:(fb_infor.w-C_WIDTH);
        my = my<(fb_infor.h-C_HEIGH)?my:(fb_infor.h-C_HEIGH);
        save_cursor(mx,my);
        prin_cursor(mx, my);
        usleep(1000);
    }
    

}




