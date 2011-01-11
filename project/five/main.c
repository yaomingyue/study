#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include "main.h" 


v_info_t fb_v;

void create_scr_fb( void)
{
    int fd;
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

    printf("w = %d\th = %d\tbpp = %d\t\n",fb_v.w,fb_v.h,fb_v.bpp);


    
}
int main(void)
{
   create_scr_fb(); 
    return 0;
}
