
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

#define SERVER_PORT		20001
#define BUFFER_SIZE		256

char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
	int i,n,len;
    int x = 0;
	int client_sock;
	socklen_t server_len;
	struct sockaddr_in server;

    char add[255] = "10.1.14.39";

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
	server.sin_addr.s_addr = inet_addr(add);
   
    
//	inet_aton(argv[1], &server.sin_addr);

	// communication with server
            buffer[0] = i;
            len = 15;
            server_len = sizeof(server);
            n = sendto(client_sock, buffer, len, 0, (struct sockaddr *)&server, server_len);
	while(1)
	{
		
        if((len = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
        {
        server_len = sizeof(server);
            
        }
        	
            //if(buffer[0] == '.') break;
        
            server_len = sizeof(server);
            n = recvfrom(client_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server, &server_len);
            if(n > 0)
            {
                i = write(STDOUT_FILENO, buffer, n);
                printf("\n");
                x = 0;
            }
            sleep(1);
	}

	close(client_sock);

	exit(EXIT_SUCCESS);
}
