#include "main.h"
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

#define SER_PORT 20000

int main(int argc, const char *argv[])
{
    int server_sock, client_sock;//套接字描述符
    int rec_len;
    struct sockaddr_in server, client;
    socklen_t addrlen;
    char *buff[10] = {0};
    char str[256];
//socket();
    if((server_sock = socket(AF_INET, SOCK_STREAM, 0)) > 0)
    printf("socket ok\n");

////bind();
    server.sin_family = AF_INET;
    server.sin_port = htons(SER_PORT);
    server.sin_addr.s_addr = htons(INADDR_ANY);
    if( !bind(server_sock, (struct sockaddr *)&server, sizeof(server)))
    printf("bind ok\n");

//listen();
    if(!listen(server_sock, 20))
    printf("listen ok\n");

//accept();
    addrlen = sizeof(client); 
    if((client_sock = accept(server_sock, (struct sockaddr *)&client, &addrlen)) > 0)
        //if((client_sock = accept(server_sock, NULL, NULL)) > 0)
    printf("accept ok\n");
    
    while(rec_len = read(client_sock, buff, 10))
    {
        printf("recived form %s at port %d \n",inet_ntop(AF_INET, &client.sin_addr, str, sizeof(str)), ntohs(client.sin_port));
        printf("receive %d bytes ok\n",rec_len);
        write(client_sock, buff, rec_len);
    }

    return 0;
}

