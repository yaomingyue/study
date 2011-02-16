#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"


void prin_board(void)
{
    int i = 0, j = 0;
    for (i = 0; i < P_NUM ; i++) 
    {
        prin_line(START_X,START_Y+SPANCE*i,START_X+SPANCE*(V_NUM-1),START_Y+SPANCE*i,0x00ff0000); 
    }
    for (i = 0; i < V_NUM ; i++) 
    {
        prin_line(START_X+SPANCE*i,START_Y,START_X+SPANCE*i,START_Y+SPANCE*(P_NUM-1),0x00ff0000); 
    }
}
