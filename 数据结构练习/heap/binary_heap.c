#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3

struct heap{
    int capacity;
    int size;
    int *unit;
};

typedef struct heap *Heap;


Heap Initialize(int size)
{
    Heap heap;

    heap = malloc(sizeof(struct heap));

    heap->unit = malloc(sizeof(int) * (size + 1));

    heap->capacity = size;
    heap->size = 0;
    heap->unit[0] = 0;
    return heap;
}


int IsEmpty(Heap heap)
{
    return heap->size == 0;
}


int IsFull(Heap heap)
{
    return heap->capacity == heap->size;
}


void Insert(Heap heap, int unit)
{
    if(IsFull(heap))
    {
        return;
    }

    // Percolate up.
    int i;
    for(i = ++heap->size; heap->unit[i/2] > unit; i/=2)
    {
        heap->unit[i] = heap->unit[i/2];
    }
    heap->unit[i] = unit;
}


void BuildHeap(Heap heap)
{
    int child, j, tmp;

    for(int i = heap->size / 2; i > 0; --i)
    {
        // Percolate down.

        for(j = i; j * 2 <= heap->size; j = child)
        {
            tmp = heap->unit[j];
            child = 2 * j;
            if(child != heap->size && heap->unit[child + 1] < heap->unit[child])
            {
                ++child;
            }
            if(heap->unit[j] > heap->unit[child])
            {
                heap->unit[j] = heap->unit[child];
                heap->unit[child] = tmp;
            }
            else
            {
                break;
            }
        }
    }
}


int DeleteMin(Heap heap)
{
    int min_unit, last_unit;

    if(IsEmpty(heap))
    {
        return heap->unit[0];
    }

    min_unit = heap->unit[1];
    last_unit = heap->unit[heap->size--];

    // Percolate one leave.
    int i, child;
    for(i = 1; i * 2 <= heap->size; i = child)
    {
        child = i * 2;
        if(child != heap->size && heap->unit[child + 1] < heap->unit[child])
        {
            ++child;
        }
        if(last_unit > heap->unit[child])
        {
            heap->unit[i] = heap->unit[child];
        }
        else
        {
            break;
        }
    }
    heap->unit[i] = last_unit;

    return min_unit;
}


int FindMin(Heap heap)
{
    if(IsEmpty(heap))
    {
        return heap->unit[0];
    }
    else
    {
        return heap->unit[1];
    }
}


void Destory(Heap heap)
{
    free(heap->unit);
    free(heap);
}



int main()
{
    Heap heap;
    heap = Initialize(MAX_SIZE);
    srand(0);
    for(int i = 1; i <= MAX_SIZE; ++i)
    {
        int j = random()%1000;
        heap->unit[i] = j;
        heap->size += 1;
        printf("Insert %d\n", j);
    }
    BuildHeap(heap);

    while(!IsEmpty(heap))
    {
        printf("DeleteMin: %d\n", DeleteMin(heap));
    }


    for(int i = 1; i <= MAX_SIZE; ++i)
    {
        int j = random()%1000;
        Insert(heap, j);
        printf("Insert %d\n", j);
    }

    while(!IsEmpty(heap))
    {
        printf("DeleteMin: %d\n", DeleteMin(heap));
    }

    Destory(heap);
    return 0;
}
