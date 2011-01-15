#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "main.h"  


v_info_t fb_v;
extern unsigned char k2[3145736] ;

void create_scr_fb( void)
{
    int fd;
    u32_t *p;
    struct fb_var_screeninfo fb_var;
    fd = open("/dev/fb0",O_RDWR);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) <0) 
    {
        perror("ioctl");
        exit(1);
    }

    fb_v.w = fb_var.xres;
    fb_v.h = fb_var.yres;
    fb_v.bpp = fb_var.bits_per_pixel;

    //printf("w = %d\th = %d\tbpp = %d\t\n",fb_v.w,fb_v.h,fb_v.bpp);

    p = mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8, PROT_WRITE, MAP_SHARED, fd, 0);
    fb_v.fbmem = p;
    close(fd);
}
void one_pixel(int x, int y, u32_t color)
{
    u32_t *p;
    if(color != 0xff000000)
    {
        p = fb_v.fbmem;
        p[x+y*fb_v.w] = color;
    }
}
int get(int *x, int *y)
{
    char c;
    scanf("%d %d%c",x,y,&c);
    return 0;
}
int main(void)
{
    int i = 0;
    char *k; 
     //char c;
     int x = 220;
     int y = 240;
     create_scr_fb(); 

    
     k = fb_v.fbmem;

     memset(k,0,1024*768*4);
    for (i = 0; i < fb_v.w*fb_v.h*fb_v.bpp/8; i++) 
    {
        k[i] = k2[i];
    }

     print_board(24,30,fb_v);
     mouse_doing();


      sleep(9); 

 #if 0
     draw_circle(120, 55);
     draw_cursor(x, y);
      sleep(3); 
     restore_shape(x, y);
     draw_cursor(x+50, y+50);
      sleep(3); 
     while(1);
     //{
       if(!get(&x,&y))
         fb_circle(x, y, 10, 0x0000ff00);
     scanf("%c",&c);
     //}
         //sleep(9); 
 #endif
     //memset(k,0,1024*768*4);
     return 0;
}
