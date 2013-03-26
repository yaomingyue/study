#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Queue{
    int size;
    int head;
    int tail;
    int *arry;
}queue;

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
int initQueue(int capacity)
{
    queue.arry = (int *)malloc(capacity*sizeof(int));
    if(queue.arry==NULL)
    {
        printf("can not malloc for arry\n");
        return -1;
    }
    queue.size = 0;
    queue.head = 0;
    queue.tail = -1;

    return 0;
}
int inQueue(int a, int capacity)
{
    pthread_mutex_lock(&queue_mutex);
    if(queue.size == capacity){
        printf("arry is full\n");
        pthread_mutex_unlock(&queue_mutex);
        return 1;     
    }
    else{
        queue.size += 1;
        queue.tail += 1;
        if(queue.tail == capacity)
            queue.tail = 0;
        queue.arry[queue.tail] = a;
    }
    pthread_mutex_unlock(&queue_mutex);
    return 0;

}
int outQueue(int capacity)
{
    int temp = 0;
    pthread_mutex_lock(&queue_mutex);
    if(queue.size == 0){
        printf("arry is empty\n");

        pthread_mutex_unlock(&queue_mutex);
        return -1;     
    }
    else{
        queue.size -= 1;
        temp = queue.arry[queue.head];
        queue.head += 1;
        if(queue.head == capacity)
            queue.head = 0;
    pthread_mutex_unlock(&queue_mutex);

    return temp;
        
    }

}
void *taskOne(void *arg)
{
    int i = 0;
    int err = 0;

    printf("this is thread one\n");
    //while(1)
    for (i = 0; i < 30; i++) 
    {
        sleep(1);
        if(err=inQueue(i, *(int *)arg))
            continue;
        //i++;
    }
    printf("thread one end\n");

    return 0;
}
void *taskTwo(void *arg)
{
    int i = 0;
    int result;

    printf("this is thread two\n");
    //while(1)
    for (i = 0; i < 30 ; i++) 
    {
        //printf("this is thread two:%d\n",i);
        sleep(1);
        if((result=outQueue(*(int *)arg)) == -1)
            continue;
        printf("%d\n",result);
    }
    printf("thread two end\n");

    return 0;
}
int main(int argc, const char *argv[])
{
    int capacity1 = 10; 
    int capacity2 = 10; 
    int err;
    pthread_t tidOne;
    pthread_t tidTwo;

    if((err=initQueue(capacity1)) != 0)
        printf("init error\n");

    err = pthread_create(&tidOne, NULL, taskOne, (void *)&capacity1);
    if(err != 0)
        printf("creat thread one failed\n");

    err = pthread_create(&tidTwo, NULL, taskTwo, (void *)&capacity2);
    if(err != 0)
        printf("creat thread two failed\n");

    pthread_join(tidOne, NULL);
    printf("thread one is joined\n");
    pthread_join(tidTwo, NULL);
    
    return 0;
}
