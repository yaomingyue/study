#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT		20001
#define BUFFER_SIZE		256

char buffer[BUFFER_SIZE];

int main(void)
{
	char c;
	int i,len,n;
	int server_sock,client_sock; //套接字描述符
	struct sockaddr_in server,client;   //internet套接字地址结构
    //struct in_addr in;//主机地址数据类型,包涵再套接字地址结构中
	// 1. create socket - create an endpoint for communication
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket ok\n");
	// 2. bind - bind a name to a socket
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;//协议或地址族
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htons(INADDR_ANY);
	bind(server_sock, (struct sockaddr *)&server, sizeof(server));
    printf("bind ok\n");
	// 3. listen - listen for connections on a socket 
	listen(server_sock, 5);
    printf("lister ok\n");
	// 4. accept - accept a connection on a socket
	while(1)
	{
		client_sock = accept(server_sock, NULL, NULL);
        printf("accept a new client ok\n");
		// receive from client
		while((len = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0)
		{
			if(buffer[0] == '.') break;	
			// lower to upper	
			for(i=0; i<len; i++)
			{
				c = buffer[i];
				buffer[i] = toupper(c);
			}
			// send back to client
			n = send(client_sock, buffer, len, 0);
		}
		close(client_sock);
		printf("Client close the connect, wait for new connect\n");
		printf("\n");
	}
	close(server_sock);
	exit(EXIT_SUCCESS);
}

