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

#define SOCKET_PORT 20001
#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];


int main(int argc, const char *argv[])
{
    int i, len;
    int server_sock;
    sockaddr_in server, client;
    socklen_t client_len;

    server_sock = sock(AF_INET,SOCK_DGRAM, 0);

    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = SOCKET_PORT;
    server.sin_addr.saddr = htons
    
    return 0;
}
