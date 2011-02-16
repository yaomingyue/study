#ifndef _MAIN_H_

#define START_X 100
#define START_Y 40
#define SPANCE 40
#define CHESS_SIZE 10

#define V_NUM 20
#define P_NUM 15

typedef unsigned int u32_t;
typedef struct
{
int w;
int h;
int bpp;
u32_t *fbmem;
}fb_info;




void prin_line(int x1, int y1, int x2, int y2, u32_t color);
void pr_one_pixel(int x, int y,int color);
void prin_board(void);
int fb_circle(int x0, int y0, int r, u32_t color);
void prin_one_chess(int x, int y);
void prin_cursor(int x, int y);
void mosedoing();







#endif

