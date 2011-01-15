#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define SERVER_PORT 20001
#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
    char c;
    int len;
    int server_sock, client_sock;
    struct sockaddr_in server, client;
    socklen_t client_len;
    struct in_addr in;
	
	// 1. create socket - create an endpoint for communication
	// int socket(int domain, int type, int protocol);
    if((server_sock = socket(AF_INET, SOCK_DGRAM,0)) < 0)
    {
        fprintf(stderr,"%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("socket ok\n");
    }


    //2 bind();
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htons(INADDR_ANY);

    if(bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
       fprintf(stderr,"%s\n",strerror(errno));
       exit(EXIT_FAILURE);
    }
    else
    {
        printf("bind addr ok\n");
        printf("\n");
    }

    while(1)
    {
        client_len = sizeof(client);
        len = recvfrom(server_sock,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client,&client_len);

        if(len < 0)
        {
            fprintf(stderr,"%s\n",strerror(errno));
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("recvfrom ok\n");
            in.s_addr = client.sin_addr.s_addr;
            printf("client ip is;%s\n",inet_ntoa(in));
            printf("client port:%d\n",ntohs(client.sin_port));
            printf("\n");
        }
        sendto(server_sock, buffer, len, 0, (struct sockaddr *)&client, client_len);

    }

     printf("client close the socket\n");
     close(server_sock);
     exit(EXIT_SUCCESS);


    return 0;
}
