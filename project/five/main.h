#ifndef _MAIN_H_
#define _MAIN_H_


typedef unsigned int u32_t;
typedef unsigned char u8_t;
typedef struct
{
    int w;
    int h;
    int bpp;
    void *fbmem;
}v_info_t;

#endif
