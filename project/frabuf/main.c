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
            dis_px(i,j,p,k2);

   for (j = 0; j < 384; j++) 
       for (i = 0; i < 512; i++) 
       for (k = 0; k < 4; k++) 
       {
        p[j*1024*4+i*4+k] = k2[j*1024*4*2+i*4*2+k];
       }
       sleep(5);

    k = 0;
   //show as circle
    while(k<640)
    {
         for (j = 0; j < 768; j++) 
                for (i = 0; i < 1024; i++) 
                    if(((i-512)*(i-512)+(j-384)*(j-384)>=k*k)&&((i-512)*(i-512)+(j-384)*(j-384)<(k+1)*(k+1)))
                    dis_px(i,j,p,kkkk);
         k++;
    }
   
       k = 0; 
   //show as circle
    while(k<640)
    {
         for (j = 0; j < 768; j++) 
                for (i = 0; i < 1024; i++) 
                    if(((i-512)*(i-512)+(j-384)*(j-384)<k*k))
                    dis_px(i,j,p,k2);
         k++;
    }
    
   //show as spuar 
   for (k = 0; k < 383; k++) 
   {
       for (j = 384-k; j <= 384+k; j++) 
       {
            dis_px(512+k,j,p,kkkk);
            dis_px(512-k,j,p,kkkk);
       }
       for (i = 512-k; i <= 512+k; i++) 
       {
            dis_px(i,384+k,p,kkkk);
            dis_px(i,384-k,p,kkkk);
       }
       usleep(3000);
   }
   for (i = 383; i < 511; i++) 
   {
       for (j = 0; j < 768; j++) 
       {
            dis_px(i+512,j,p,kkkk);
            dis_px(512-i,j,p,kkkk);
       }
       usleep(3000);
   }



    //up and down
   for (j = 0; j < 383; j++) 
   {
       for (i = 0; i < 1024; i++) 
       {
            dis_px(i,383+j,p,k2);
            dis_px(i,383-j,p,k2);
       }
       usleep(3000);
   }
   //left and right
   for (i = 0; i < 511; i++) 
   {
       for (j = 0; j < 768; j++) 
       {
            dis_px(i+512,j,p,kkkk);
            dis_px(512-i,j,p,kkkk);
       }
       usleep(3000);
   }

       //down

       for (j = 0; j < 768; j++) 
       {
            for (i = 0; i < 1024; i++) 
                dis_px(i,j,p,k2);
            usleep(3000);
       }

      //ringt 
       for (i = 0; i < 1024; i++) 
       {
            for (j = 0; j < 768; j++) 
                dis_px(i,j,p,kkkk);
            usleep(3000);
       }



   sleep(10);
   memset(p,0,1024*768*4);
   
   close(fd); 
    return 0;
}



