#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SOCK_PORT 20001
#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];


int main(int argc, const char *argv[])
{
    int len;
    int server_sock, client_sock;
    sockaddr_in server, client;
    socklen_t client_len;


    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    return 0;
}
