#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
//#include "common.h"
#include <fcntl.h>
extern unsigned char kkkk[172808];
extern unsigned char k2[172808];
#define fb_dev "/dev/fb0"
    typedef struct
    {
    int w;
    int h;
    int bpp;
    char *fbmem;
    }fb_info;

int init_fb(fb_info *fb_inf)
{
   int fd;
   fd = open(fb_dev,O_RDWR);
   struct fb_var_screeninfo fb_var;
   ioctl(fd,FBIOGET_VSCREENINFO,&fb_var);

   fb_inf->w = fb_var.xres;
   fb_inf->h = fb_var.yres;
   fb_inf->bpp = fb_var.bits_per_pixel;
   printf("w:%d\t%d\t%d\n",fb_inf->w,fb_inf->h,fb_inf->bpp);
}
void dis_px(int x, int y, char *p, unsigned char *k)
{
    int i;
    for (i = 0; i < 4; i++) 
    {
        p[y*1024*4+x*4+i] = k[y*1024*4+x*4+i];
    }
}

int main(int argc, const char *argv[])
{
   char *p;
   int fd;
   int i = 0,j = 0,k = 0, m = 0;
   fd = open(fb_dev,O_RDWR);
   fb_info *fb_inf;
   p = mmap(NULL,1024*768*4,PROT_WRITE,MAP_SHARED,fd,0);



       for (j = 0; j < 768; j++) 
            for (i = 0; i < 1024; i++) 
                dis_px(i,j,p,kkkk);
       for (j = 0; j < 768; j++) 
       {
            for (i = 0; i < 1024; i++) 
                dis_px(i,j,p,k2);
            usleep(3000);
       }




       for (j = 0; j < 768; j++) 
            for (i = 0; i < 1024; i++) 
                dis_px(i,j,p,kkkk);
       
       for (i = 0; i < 1024; i++) 
       {
            for (j = 0; j < 768; j++) 
                dis_px(i,j,p,k2);
            usleep(3000);
       }

      memset(p,0,1024*768*4);
     

       for (j = 0; j < 768; j++) 
            for (i = 0; i < 1024; i++) 
                if(((i-512)*(i-512)+(j-384)*(j-384)>10000)&&((i-512)*(i-512)+(j-384)*(j-384)<40000))
                dis_px(i,j,p,kkkk);
    



   sleep(10);
   memset(p,0,1024*768*4);
    
    return 0;
}



