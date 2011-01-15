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


#define SERVER_PORT 20001
#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];




int main(int argc, const char *argv[])
{
    int n, len;
    sockaddr_in server, client;
    int client_sock;
    socklen_t server_len;

    if(argc < 2)
    {
        printf("\n");
        printf("sorry , you type is wrong\n");
        printf("usage: %s x.x.x.x(server ip)\n",argv[0]);
        printf("\n");
        exit(EXIT_FAILURE);
    }
    if((client_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        fprintf(stderr,"%s",strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("creat socket ok!"\n);
    }
    bzero(&server,sizeof(server));
    serve.sin_family = AF_INET;
    serve.sin_port = htons(SERVER_PORT);
    serve.sin_addr.s_addr = inet_addr(argv[1]);
     
    
    return 0;
}
