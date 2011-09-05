#include "main.h"
int main(int argc, const char *argv[])
{
    FILE *dk = NULL;
    int i = 0;
    char *buff[255] = {0};

    dk = fopen("yao","r");

    while( fscanf(dk, "%s", buff) > 0){
        printf("%s\n",buff);
    }
#if 0
    for (i = 0; i < 100; i++) 
    {
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d",i);
        fprintf(dk, "%d\n",i);
        
    }
#endif 

    fclose(dk);
    
    return 0;
}
