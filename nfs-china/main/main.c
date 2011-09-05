#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DATA_SIZE 256

int main(int argc, const char *argv[])
{
    int fd = 0;
    char data[DATA_SIZE] = {0};
    fd = open ("moon", O_RDWR);
    //fd = open ("/dev/ttyS0", O_RDWR|O_NONBLOCK);
    if (fd == -1) {
        printf("open error\n");
        return -1;
    }

    struct termios term;
    if (tcgetattr (fd, &term) < 0) {//获取描述符为fd的终端的参数
        printf("tcgetattr error\n");
        //return -1;
    }

    cfmakeraw(&term);//设置为流
    cfsetispeed(&term, 115200);//波特率

    if (tcsetattr (fd, TCSAFLUSH, &term) < 0) { //设置参数,term中存着要改的参数
        printf("tcsetattr error\n");
        //return -1;
    }

    write(fd, "yaomoon", sizeof("yaomoon") - 1);
    //read(fd, data, DATA_SIZE);

    return 0;
}
