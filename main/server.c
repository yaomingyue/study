#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 20000
#define BUFFER_SIZE 11 

char buffer[BUFFER_SIZE];

int main(void)
{
    char c;
    int i, len, n;
    int server_sock, client_sock;
    struct sockaddr_in server, client;
    int fd;

    fd = open("yao", O_RDWR|O_CREAT, 0644); 

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&server, sizeof(server));
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htons(INADDR_ANY);
    bind(server_sock, (struct sockaddr *)&server, sizeof(server));

    listen(server_sock, 5);

    while(1)
    {
        client_sock = accept(server_sock, NULL, NULL);

        while((len = recv(client_sock, buffer,BUFFER_SIZE, 0)) > 0)
        {
            write(fd, buffer, len);
            //n = send(client_sock, " ", 1, 0);
        }
        close(client_sock);
        printf("client close the connect, wait for new connect\n");
        printf("\n");
    }
    close(server_sock);
    close(fd);

    return 0;
}
