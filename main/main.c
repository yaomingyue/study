#include <stdio.h>
float cal_money(float distance,long wait_time, int day)
{
    float money;
    wait_time = wait_time / 300;
    printf("%ld\n",wait_time );
    distance = distance + wait_time;
    if(day)
    {
       money = distance < 3 ? 10 : (distance - 3) * 2 + 10 ; 
       if(distance > 15)
       money = money + (distance - 15) * 1;
       return money;
    }
    else
    {
       money = distance < 3 ? 11 : (distance - 3) * 2.4 + 11 ; 
       if(distance > 15)
           money = money + (distance - 15) * 1.2;
       return money;
    }

}
int main(int argc, const char *argv[])
{
   float money, diatance, time;
   money = cal_money(16,20,1);
   printf("%1.2f\n",money);
    
    return 0;
}
