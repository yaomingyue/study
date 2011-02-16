#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>

#include "main.h"


fb_info fb_infor;

void frambuff_init(fb_info *infor)
{
   int fd;
   int *k;
   struct fb_var_screeninfo fb_var;
   fd = open("/dev/fb0", O_RDWR);

   ioctl(fd,FBIOGET_VSCREENINFO,&fb_var);
   infor->w = fb_var.xres;
   infor->h = fb_var.yres;
   infor->bpp = fb_var.bits_per_pixel;
   //printf("%d  %d  %d\n",infor->w, infor->h, infor->bpp);
   k = mmap(NULL, infor->w*infor->h*infor->bpp/8,PROT_WRITE,MAP_SHARED,fd,0);
   infor->fbmem = k;
    
}
void pr_one_pixel(int x, int y,int color)
{
    int *k = fb_infor.fbmem;
    k[y*fb_infor.w + x] = color;
    
}
int main(int argc, const char *argv[])
{
   int i = 0;
   int *k;
   frambuff_init(&fb_infor);
   k = fb_infor.fbmem;
   //prin_line(0,50,500,80,0x00ff0000);
    prin_board();
    prin_one_chess(100, 40);
    prin_one_chess(130, 40);
    //prin_cursor(500, 320);

    mosedoing();

    return 0;
}
