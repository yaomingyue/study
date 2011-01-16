
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

#define SERVER_PORT		20001
#define BUFFER_SIZE		256

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
int i,len;
int x = 3, y = 2;
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
        x = p->x;
        y = p->y;
       printf("%d\n",x);
       printf("%d\n",y);
    }
    
}
void send_msg(int x, int y)
{
    p->x = x;
    p->y = y;
    sendto(server_sock, buffer, len, 0, (struct sockaddr *)&client, client_len);
}

int main(int argc, char *argv[])
{
	
	// 1. create socket - create an endpoint for communication
	if ((server_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("create socket ok!\n");
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
		printf("bind addr ok!\n");
		printf("\n");
	}

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
			printf("recvfrom client ok!\n");
			in.s_addr = client.sin_addr.s_addr;
			printf("client ip  : %s\n", inet_ntoa(in));
			printf("client port: %d\n", ntohs(client.sin_port));
			printf("\n");
		}
	while(1)
	{
       send_msg(x,y);
       receive_msg();
        sleep(2);
        x++;
	}

	printf("Client close the socket\n");
	close(server_sock);

	exit(EXIT_SUCCESS);
}

