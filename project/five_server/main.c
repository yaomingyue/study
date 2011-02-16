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


v_info_t fb_v;
extern int cx, cy;
extern unsigned char k2[3145736];

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
    pthread_t id;
    int ret;
    create_scr_fb(); 
    k = fb_v.fbmem ;


     memset(k,0,1024*768*4);

#if 0
    while(i<1024*768)
     {
        k[i] = 0x00db9a4a;  
        i++;
     }
    
     k = fb_v.fbmem;

     memset(k,0,1024*768*4);
#endif
    for (i = 0; i < fb_v.w*fb_v.h*fb_v.bpp/8; i++) 
    {
        k[i] = k2[i];
    }

    print_board(24,30,fb_v);
    server_init();

    ret = pthread_create(&id,NULL,(void *)mouse_doing,NULL);
    if(ret!=0)
    {
        printf("error\n");
        exit(1);
    }
    while(1) 
    {
       receive_msg();
    }

     return 0;
}
