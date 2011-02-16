#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <fcntl.h>
#include "main.h"  

extern unsigned char k2[1024*768*4];
v_info_t fb_v;
extern int cx, cy;

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

int main(int argc, const char *argv[])
{
    int i = 0;
    char *k; 
    pthread_t id;
    int ret;
    
    create_scr_fb(); 
    k = fb_v.fbmem ;
    if(argc < 2)
    {
         printf("\n");
         printf("sorry,your type is wrong\n");    
         printf("usage: %s x.x.x.x(server ip)\n",argv[0]);
         exit(EXIT_FAILURE);
    }

    //背景，画棋盘 
    memset(k, 0, 1024*768*4);
    for (i = 0; i < fb_v.w*fb_v.h*fb_v.bpp/8; i++) 
    {
        k[i] = k2[i];
    }
     print_board( 24, 30, fb_v);
     client_init(argv[1]);

     //新建线程用于查看鼠标动作
     ret = pthread_create(&id, NULL, (void *)mouse_doing, NULL);
     if(ret! = 0)
     {
        printf("error\n");
        exit(1);
     }

    //等待接受数据
     while(1) 
     {
         recv_msg();
     }

     return 0;
}
