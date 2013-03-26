
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
#include "curses.h"

#define ADDR "127.0.0.1"
#define SERVER_PORT		20000
#define BUFFER_SIZE		256

char buffer[BUFFER_SIZE];

int getString(char *str)
{
    int len = 0;
    //len = read(STDIN_FILENO, str, BUFFER_SIZE);

    tablet_str(str);
    return strlen(str);
}
void displayString(char *str)
{
    moon_str(str);
    printf("##################receive from server%s\n",str);
}
void error_exit(void)
{
}

int main(int argc, char *argv[])
{
	int n,len;
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

    init_curses();
    draw_bottom();

	if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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
	server.sin_addr.s_addr = inet_addr(ADDR);

	server_len = sizeof(server);
	if(connect(client_sock, (struct sockaddr *)&server, server_len) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("connect server ok!\n");
        len = strlen(argv[1]);
		printf("will send username:%s\n",argv[1]);
		n = send(client_sock, argv[1],len , 0);
	}

    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        while(1)
        {
            memset(buffer,0,len);
            if((len = getString(buffer)) > 0)
            {
                n = send(client_sock, buffer, len, 0);
            }
        }

        printf("process 1 exit\n");
        exit(1);

    }else if(pid < 0)
    {
        printf("%s\n",strerror(errno));
        error_exit();
    }

    pid = fork();

    if(pid == 0)
    {
        printf("process 2 created\n");
        while(1)
        {
            if((len = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0)
            {
                displayString(buffer);
            }

            memset(buffer,0,len);
        }

        printf("process 2 exit\n");
        exit(1);

    }else if(pid < 0)
    {
        printf("%s\n",strerror(errno));
        error_exit();
    }


	while(1)
	{
    /*
		n = write(STDOUT_FILENO, ">  ", 3);
	
		if((len = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
		{
			n = send(client_sock, buffer, len, 0);
		}

	 	if(buffer[0] == '.') break;

		if((len = recv(client_sock, buffer, len, 0)) > 0)
		{
			n =	write(STDOUT_FILENO, buffer, len);
		}
        */
	} 

	close(client_sock);

	exit(EXIT_SUCCESS);
}
