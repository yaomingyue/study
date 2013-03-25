#include <stdio.h>
#include <pthread.h>

pthread_cond_t has_ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int flag = 0;

void myloop(int arg, int loop)
{
    int i = 0;
    int j = 0;
    for (j = 0; j < 10 ; j++) 
    {
        while(flag == arg)
        {
            pthread_mutex_lock(&lock);
            pthread_cond_wait(&has_ready,&lock);
            pthread_mutex_unlock(&lock);
        }

        for (i = 0; i < loop; i++) 
        {
            usleep(1000);
            printf("%d",flag);
        }
        flag = !flag;
        printf("\n");
        printf("new thread loop 10 over\n");
        pthread_cond_broadcast(&has_ready);
    }

}
void *myfun(void *arg)
{
    printf("this is new thread\n");
    myloop(0,10);
}

int main(int argc, const char *argv[])
{
    
    int err;
    pthread_t tid;
    int i = 0;
    int j = 0;

    err = pthread_create(&tid,NULL,myfun,NULL);
    if(err != 0)
        printf("create error\n");

    printf("this is main thread\n");
    myloop(1,50);
    
    err = pthread_join(tid,NULL);
    if(err != 0)
        printf("join error\n");


    return 0;
}
