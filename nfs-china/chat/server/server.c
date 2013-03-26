
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

#define SERVER_PORT		20000
#define BUFFER_SIZE		256

char buffer[BUFFER_SIZE];


int main(void)
{
	char c;
	int i,len,n;
	int server_sock,client_sock; //套接字描述符
	socklen_t client_len;//地址结构的字节数大小
	struct sockaddr_in server,client;   //internet套接字地址结构
	struct in_addr in;//主机地址数据类型
	
	if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("create socket ok!\n");
	}

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
	}

	if(listen(server_sock, 1) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("listen ok!\n");
	}

    pid_t mpid;

	while(1)
	{
		client_len = sizeof(client);
		if((client_sock = accept(server_sock, (struct sockaddr *)&client, &client_len)) < 0)
		{
			close(server_sock);
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("accept client ok!\n");
			in.s_addr = client.sin_addr.s_addr;
			printf("client ip  : %s\n", inet_ntoa(in));
			printf("client port: %d\n", ntohs(client.sin_port));
		}

        mpid = fork();
        if(mpid == 0)
        {
            len = recv(client_sock, buffer, BUFFER_SIZE, 0);

            printf("receive username:%s\n",buffer);

            while((len = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0)
            {
                printf("receive new message:%s\n",buffer);
                n = send(client_sock, buffer, len, 0);

                memset(buffer,0,len);
            }
        
            close(client_sock);

            printf("Client close the connect, wait for new connect\n");
            printf("\n");
            exit(1);
        }

	}

	close(server_sock);

	exit(EXIT_SUCCESS);
}

