
#include <stdio.h>
#include <stdlib.h>

struct Queue{
    int size;
    int head;
    int tail;
    int *arry;
}queue;
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
    if(queue.size == capacity){
        printf("arry is full\n");
        return 1;     
    }
    else{
        queue.size += 1;
        queue.tail += 1;
        if(queue.tail == capacity)
            queue.tail == 0;
        queue.arry[queue.tail] = a;
    }
    return 0;

}
int outQueue(int capacity)
{
    int temp = 0;
    if(queue.size == 0){
        printf("arry is empty\n");
        return -1;     
    }
    else{
        queue.size -= 1;
        temp = queue.arry[queue.head];
        queue.head += 1;
        if(queue.head == capacity)
            queue.head == 0;

        return temp;
        
    }

}

int main(int argc, const char *argv[])
{
    int capacity = 10; 
    int err;
    int i;
    int result;

    if((err=initQueue(capacity)) != 0)
        printf("init error\n");

    for (i = 0; i < 8; i++) 
    {
        if(err=inQueue(i, capacity))
            break;
    }
    for (i = 0; i < 11; i++) 
    {
        if((result=outQueue(capacity)) == -1)
            break;
        else
            printf("%d\n",result);
    }
    for (i = 8; i < 16; i++) 
    {
        if(err=inQueue(i, capacity))
            break;
    }
    for (i = 0; i < 11; i++) 
    {
        if((result=outQueue(capacity)) == -1)
            break;
        else
            printf("%d\n",result);
    }
    
    return 0;
}
