/*
    The C code are used to practise the simple usage of queue.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int unit;
    struct node *font;
    struct node *rear;
}*Node;


typedef struct queue{
    int size;
    Node head;
    Node rear;
}*Queue;


// Create a queue.
Queue CreateQueue()
{
    Queue queue;
    queue = malloc(sizeof(Queue));
    queue->size = 0;
    queue->head = NULL;
    queue->rear = NULL;
    return queue;
}


// Judge whether the queue is empty.
int IsEmpty(Queue q)
{
    if(q->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// Make a element enqueue.
void Enqueue(Queue q, int unit)
{
    Node node = malloc(sizeof(Node));
    node->unit = unit;
    node->rear = NULL;

    if(IsEmpty(q))
    {
        node->font = NULL;
        q->head = node;
        q->rear = node;
    }
    else
    {
        node->font = q->rear;
        q->rear->rear = node;
        q->rear = node;
    }
    q->size += 1;
}


// Make a element dequeue.
void Dequeue(Queue q)
{
    if(!IsEmpty(q))
    {
        Node node;
        node = q->head;
        if(q->head->rear != NULL)
        {
            q->head->rear->font = NULL;
            q->head = q->head->rear;
        }
        else
        {
            q->head = NULL;
        }
        free(node);
        q->size -= 1;
    }
}


int main()
{
    Queue q;
    q = CreateQueue();

    for(int i = 0; i < 10; ++i)
    {
        Enqueue(q, i);
        printf("Enqueue element: %d\n", i);
    }

    while(!IsEmpty(q))
    {
        printf("Obtain queue node: %d\n", q->head->unit);
        Dequeue(q);
    }

    free(q);
    return 0;
}
