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
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT		20001
#define BUFFER_SIZE		256

char buffer[BUFFER_SIZE+2];

#define REGISTER_MSG	0x10
#define INFORMATION_MSG	0x20

//
//
int main(int argc, char *argv[])
{
	fd_set input_fd;
	int local_id,remote_id;
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

	printf("input local user id: ");
	n = scanf("%d", &local_id);
	printf("input remote user id: ");
	n = scanf("%d", &remote_id);

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

	buffer[0] = REGISTER_MSG;
	buffer[1] = local_id;
	server_len = sizeof(server);
	n = sendto(client_sock, buffer, 2, 0, (struct sockaddr *)&server, server_len);

	// communication with server
	while(1)
	{
		FD_ZERO(&input_fd);
		FD_SET(STDIN_FILENO, &input_fd);
		FD_SET(client_sock, &input_fd);

		// write to screen
		i = write(STDOUT_FILENO, ">  ", 3);
//		i = write(fileno(stdout), ">  ", 3);
		
		if((select(client_sock+1, &input_fd, NULL, NULL, NULL)) < 0)
		{
			fprintf(stderr, "%s\n", strerror(errno));
			continue;
		}

		if(FD_ISSET(STDIN_FILENO, &input_fd))
		{
			// read from keyboard	
			if((len = read(STDIN_FILENO, (char *)&buffer[2], BUFFER_SIZE)) > 0)
//			if((len = read(fileno(stdin), buffer, BUFFER_SIZE)) > 0)
			{
				// send to server
				server_len = sizeof(server);
				buffer[0] = INFORMATION_MSG;
				buffer[1] = remote_id;
				n = sendto(client_sock, buffer, len+2, 0, (struct sockaddr *)&server, server_len);
			}
		}

		// Quit flag	
//	 	if(buffer[0] == '.') break;
	
		if(FD_ISSET(client_sock, &input_fd))
		{
			// receive message from server	
			server_len = sizeof(server);
			n = recvfrom(client_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server, &server_len);
			if(n > 0)
			{
				// write to screen
				i = write(STDOUT_FILENO, "\n", 1);
				i = write(STDOUT_FILENO, buffer, n);
//				i = write(fileno(stdout), buffer, n);
			}
		}
	}

	close(client_sock);

	exit(EXIT_SUCCESS);
}
