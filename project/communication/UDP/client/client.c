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
* Description   : network client demo program in UDP mode.
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

<<<<<<< HEAD
#define SERVER_PORT		9100
=======
<<<<<<< HEAD
#define SERVER_PORT		8100
=======
#define SERVER_PORT		7100
>>>>>>> d0cc73cff2742688337122f34cb71af6eacfbacb
>>>>>>> 1063dc4d3afeb3ba7d351d876629ae175b3e58fe
#define BUFFER_SIZE		256

char buffer[BUFFER_SIZE];

//
//
int main(int argc, char *argv[])
{
	int i,n,len;
	int client_sock;
	socklen_t server_len;
	struct sockaddr_in server;

	if(argc < 2)
	{
		printf("\n");
		printf("Sorry, your type is wrong.\n");
		printf("Usage: %s x.x.x.x(server IP)\n", argv[0]);
		printf("\n");
		exit(EXIT_FAILURE);
	}

	// 1. create socket - create an endpoint for communication
	// int socket(int domain, int type, int protocol);
	if ((client_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("create socket ok!\n");
	}

	// make server address information
	bzero(&server, sizeof(server));
//	memset(&server, 0, sizeof(server));
	
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(argv[1]);
   
    
//	inet_aton(argv[1], &server.sin_addr);

	// communication with server
	while(1)
	{
		// write to screen
		i = write(STDOUT_FILENO, ">  ", 3);
//		i = write(fileno(stdout), ">  ", 3);
		
		// read from keyboard	
		if((len = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
//		if((len = read(fileno(stdin), buffer, BUFFER_SIZE)) > 0)
		{
			// send to server
			server_len = sizeof(server);
			n = sendto(client_sock, buffer, len, 0, (struct sockaddr *)&server, server_len);
            printf("%s\n",buffer);
		}
	
		// Quit flag	
	 	if(buffer[0] == '.') break;
	
		// receive message from server	
		server_len = sizeof(server);
		n = recvfrom(client_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server, &server_len);
		if(n > 0)
		{
			// write to screen
			i = write(STDOUT_FILENO, buffer, n);
//			i = write(fileno(stdout), buffer, n);
		}
	}

	close(client_sock);

	exit(EXIT_SUCCESS);
}
