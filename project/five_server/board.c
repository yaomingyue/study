#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

void print_board(int h_num, int v_num, v_info_t fb_v)
{
    int i;
    int w, h;
    w = fb_v.w;
    h = fb_v.h;

      //v
      for (i = 0; i < 30; i++) 
      {
          fb_line(START_X+i*SPACE, START_Y,START_X+i*SPACE, START_Y+(P_NUM-1)*SPACE, 0x00ff0000);
      }
      //h
      for (i = 0; i < 24; i++) 
      {
          fb_line( START_X, START_Y+i*SPACE, START_X+(V_NUM-1)*SPACE, START_Y+i*SPACE, 0x00ff0000);
      }
}
