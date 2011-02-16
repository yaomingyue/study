
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"

#define SERVER_PORT		20001
#define BUFFER_SIZE		256

extern u32_t color_choice;
extern char who;

unsigned char buffer[BUFFER_SIZE];
typedef struct {
char dest;
char source;
char type;
char len;
int x;
int y;
}msg;
msg *p = (msg *)buffer;


char c;
int i,len = 12;
int x = 3, y = 2;
int cx, cy;
int server_sock;
socklen_t client_len;
struct sockaddr_in server,client;
struct in_addr in;

void receive_msg(void)
{
    client_len = sizeof(client);
    len = recvfrom(server_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &client_len);
    if (len >= 0)
    {
       cx = p->x;
       cy = p->y;
       cx = (cx)*SPACE + START_X;    
       cy = (cy)*SPACE + START_Y;    

       color_choice = 0x01000000;  
       who = 2;

       chess_print(cx,cy);
       check_won(cx, cy);
    }
    
}
void send_msg(int x, int y)
{
   len = 13;
   int dx = (x-START_X)%30;
   int dy = (y-START_Y)%30;
   x = (dx - 15 < 0)?x-dx:x+30-dx; 
   y = (dy - 15 < 0)?y-dy:y+30-dy; 
   x = (x - START_X)/SPACE;
   y = (y - START_Y)/SPACE;
   
   p->x = x;
   p->y = y;
   sendto(server_sock, buffer, len, 0, (struct sockaddr *)&client, client_len);
}

int server_init(void)
{
	
	// 1. create socket - create an endpoint for communication
	if ((server_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
        //printf("create socket ok!\n");
	}
	
	// 2. bind - bind a name to a socket
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htons(INADDR_ANY);

	if(bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
        //printf("bind addr ok!\n");
        //printf("\n");
	}
  #if 1
		client_len = sizeof(client);
		len = recvfrom(server_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &client_len);
		if (len < 0)
		{
			close(server_sock);
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		else
		{
            //printf("recvfrom client ok!\n");
            //in.s_addr = client.sin_addr.s_addr;
            //printf("client ip  : %s\n", inet_ntoa(in));
            //printf("client port: %d\n", ntohs(client.sin_port));
            //printf("\n");
		}
  #endif
  return 0;

}


