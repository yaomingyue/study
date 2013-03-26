
/***************************************************************************
* Module Name   : client.c                                                   
* Identification:                                                  
* Date          : 2010.09.04                                          
*                                                                        
* Author        : Yu Lianqing                                           
*                                                                        
* Copyright (c)                          
* ALL RIGHTS RESERVED                                                
*                                                                         
* Revisions of %M% :                                                    
* #.##   Name         Date          Description                        
* ----   ------------ ------------- ----------------------------------- 
*                                                                         
* Description   : network client demo program in TCP mode.
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT		20001
#define BUFFER_SIZE		256

char buffer[BUFFER_SIZE];

//
//
int main(int argc, char *argv[])
{
	int n,len;
	int client_sock;
	socklen_t server_len;
	struct sockaddr_in server;
    FILE *fp;

	if(argc < 2)
	{
		printf("\n");
		printf("Sorry, your type is wrong.\n");
		printf("Usage: %s x.x.x.x(server IP)\n", argv[0]);
		printf("\n");
		exit(EXIT_FAILURE);
	}

	// 1. create socket - create an endpoint for communication 
	// int socket(int domain, int type, int protocol) 
	if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("create socket ok!\n");
	}

	// 2. connect - initiate a connection on a socket 
	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	bzero(&server, sizeof(server));
//	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(argv[1]);
//	inet_aton(argv[1], &server.sin_addr);

	server_len = sizeof(server);
	if(connect(client_sock, (struct sockaddr *)&server, server_len) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("connect server ok!\n");
	}

	// communication with server
	while(1)
	{
        sleep(1);
		// write to screen
		n = write(STDOUT_FILENO, ">  ", 3);
//		n = write(fileno(stdout), ">  ", 3);
	
        fp = fopen("/sys/power/wake_lock","r");
        if(!fp)
        {
            printf("error:%d\n",errno);
        }

        memset(buffer,0,sizeof(buffer)); 
        len = fread(buffer,100,1,fp);
        len = strlen(buffer);
	    n = send(client_sock, buffer, len, 0);
        printf("%d  %s\n",len,buffer);
        fclose(fp);



		// receive message from server	
	} 

	close(client_sock);

	exit(EXIT_SUCCESS);
}
