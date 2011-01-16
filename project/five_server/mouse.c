#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include <unistd.h>
#include <fcntl.h>
#include "main.h"

#define X_ 0xffff
#define T_ 0xff000000
#define BORD 0x000000ff

#define C_WIDTH 10
#define C_HEIGH 17
extern v_info_t fb_v;

extern u32_t color_choice;
extern char who;

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
static u32_t shape_save[C_HEIGH*C_WIDTH];

int save_shape(int x, int y)
{
    int i = 0;
    int j = 0;
    u32_t *p = fb_v.fbmem;
    for (i = 0; i < C_HEIGH; i++) 
    {
        for (j = 0; j < C_WIDTH; j++) 
        {
            shape_save[j+i*C_WIDTH]= p[x+j+(y+i)*fb_v.w];
        }
    }
    return 0;
}

int restore_shape(int x, int y)
{
    int i = 0;    
    int j = 0;    

    for (i = 0; i < C_HEIGH; i++) 
    {
        for (j = 0; j < C_WIDTH; j++) 
        {
            one_pixel(x+j, y+i, shape_save[j+i*C_WIDTH]);
        }
    }
    return 0;
}


int draw_cursor(int x, int y)
{
   int i = 0;
   int j = 0;

   save_shape(x, y);

   for (i = 0; i < C_HEIGH; i++) 
   {
        for (j = 0; j < C_WIDTH ; j++) 
        {
            one_pixel(x+j, y+i, cursor_pixel[j+i*C_WIDTH]);
        }
   }
   return 0;
}
int get_m_info(int fd, m_event *event)
{
    char buf[8] = {0};
    int n; 
    n = read(fd, buf, 8);
    if(n < 0)
    {
        return 0;
    }
    else
    event->button = buf[0] & 0x07;
    event->dx = buf[1];
    event->dy = -buf[2];
    event->dz = buf[3];
    return n;
}


int print_choice(void)
{
    fb_circle(40,60,20,0xffffffff);
    fb_circle(40,140,20,0x01000000);
    return 0;
}

int mouse_doing(void)
{
    int *k;
    k = fb_v.fbmem;
    m_event mevent;
    int fd;

    int mx = 512;
    int my = 384;

    fd = open("/dev/input/mice",O_RDWR|O_NONBLOCK);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    draw_cursor(mx,my);

    while(1)
    {
        if(get_m_info(fd, &mevent) > 0)
        {
            restore_shape(mx,my);
            mx += mevent.dx;
            my += mevent.dy;

            mx = mx>0?mx:0;
            my = my>0?my:0;
            
            mx = mx<(fb_v.w-C_WIDTH)?mx:(fb_v.w-C_WIDTH);
            my = my<(fb_v.h-C_HEIGH)?my:(fb_v.h-C_HEIGH);

            switch(mevent.button)
            {

                case 1 :
                        color_choice =0xffffffff; 
                        who = 1;
                        if(chess_print(mx,my)) 
                        {
                             send_msg(mx,my);
                             check_won(mx, my);
                         }
                         save_shape(mx, my);
                            
                         break;
                case 2 : 
                         memset(k,0,1024*768*4);
                         print_board(24,30,fb_v);
                         break;
                case 4 : break;
               default : break;
            }
            draw_cursor(mx,my);
        }
        usleep(10000);
    }
    
}

