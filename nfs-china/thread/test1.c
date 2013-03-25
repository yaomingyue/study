#include <stdio.h>
#include <pthread.h>

struct foo {
    int a;
    int b;
    int c;
};
struct foo foo1 = {1,2,3};

void printfoo(char *s, struct foo foo)
{
    printf("%s\n",s);
    printf("foo.a =%d\n",foo.a);
    printf("foo.b =%d\n",foo.b);
    printf("foo.c =%d\n",foo.c);
}
void *my_fun1(void *arg)
{
    printf("this is thread1:%s\n",(char *)arg);

    printfoo("thread 1", foo1);
    foo1.a = 4;
    foo1.b = 5;
    foo1.c = 6;

    pthread_exit((void *)&foo1); // 将foo结构传出去，该结构不能是局部变量。 因为传出的是地址，线程退出后局部变量就被回收了。
}
void *my_fun2(void *arg)
{
    printf("this is thread2:%s\n",(char *)arg);

    pthread_exit((void *)2);
}

int main(int argc, const char *argv[])
{
    pthread_t tid1; 
    pthread_t tid2; 
    int err;
    void *tret;
    struct foo *fp;

    err = pthread_create(&tid1, NULL, my_fun1, "hellomoon");
    if(err != 0)
         printf("can not creat new thread\n");

    err = pthread_create(&tid2, NULL, my_fun2, "hellomoon");
    if(err != 0)
         printf("can not creat new thread\n");

    err = pthread_join(tid1, (void *)&fp);
    if(err != 0)
        printf("can not join thread1\n");
    printf("thread1 exit code %d\n",(int)tret);
    err = pthread_join(tid2, &tret);
    if(err != 0)
        printf("can not join thread2\n");
    printf("thread2 exit code %d\n",(int)tret);

    printfoo("mainthread", *fp);

    return 0;
}
