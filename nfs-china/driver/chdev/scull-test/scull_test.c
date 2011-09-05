#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	char buffer1[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	char buffer2[20]={0};
	int sculltest;
	int code,i;
	
	sculltest = open("/dev/scull0",O_WRONLY );
    if(sculltest < 0)
        printf("error\n");

    for ( i=20 ; i>0 ; i-=code)		{  
    if ((code=write(sculltest , &buffer1[20-i] , i)) != i) printf("write error! code=%d \n",code);
    else   printf("write ok! code=%d \n",code);
    }

	close(sculltest);


	sculltest = open("/dev/scull0",O_RDONLY );

	for ( i=20 ; i>0 ; i-=code)		{  
		if ((code=read(sculltest , &buffer2[20-i] , i)) != i) printf("read error! code=%d \n",code);
		else   printf("read ok! code=%d \n",code);
	}
	
	for(i=0;i<20;i+=5) 
		printf("[%d]=%d [%d]=%d [%d]=%d [%d]=%d [%d]=%d\n",i,buffer2[i],i+1,buffer2[i+1],i+2,buffer2[i+2],i+3,buffer2[i+3],i+4,buffer2[i+4]);

	printf("\n"); 

	close(sculltest);
  exit(0);
}
