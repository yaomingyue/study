#ifndef _MAIN_H_
#define _MAIN_H_

#define SPACE 30
#define V_NUM 30
#define P_NUM 24
#define START_X 100
#define START_Y 40
#define CHESS_SIZE 10 
#define CHESS_COLOR 0x000000ff 

typedef unsigned int u32_t;
typedef unsigned char u8_t;
typedef struct
{
    int w;
    int h;
    int bpp;
    void *fbmem;
}v_info_t;

typedef struct
{
    int dx;
    int dy;
    int dz;
    int button; 
}m_event;

extern void one_pixel(int x, int y, u32_t color);
void fb_line(int x1, int y1, int x2, int y2, u32_t color);
void print_board(int h, int v, v_info_t fb_v);
void draw_circle(int x, int y);
int fb_circle(int x0, int y0, int r, u32_t color);
int restore_shape(int x, int y);
int draw_cursor(int x, int y);
int mouse_doing(void);
int chess_count(int x, int y);
int check_all(void);
void check_won(int x, int y);
int choose_color(int x, int y);
int chess_print(int x, int y);
/*int client_init(void);*/
    int client_init(char *argv);
int recv_msg(void);
int send_msg(int x, int y);

#endif
