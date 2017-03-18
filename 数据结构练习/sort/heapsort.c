#include <stdio.h>
#include <stdlib.h>


void PercolateDown(int heap[], int len, int hole)
{
    int i, tmp, child;

    for(i = hole; i * 2 <= len; i = child)
    {
        child = 2 * i;
        tmp = heap[i];

        if(child != len && heap[child + 1] < heap[child])
        {
            ++child;
        }

        if(heap[i] > heap[child])
        {
            heap[i] = heap[child];
            heap[child] = tmp;
        }
        else
        {
            break;
        }
    }
}


void HeapSort(int heap[], int len)
{
    for(int i = len / 2; i > 0; --i)
    {
        PercolateDown(heap, len, i);
    }

    for(int i = len; i > 0; --i)
    {
        int tmp = heap[1];
        heap[1] = heap[i];
        heap[i] = tmp;
        PercolateDown(heap, i - 1, 1);
    }
}


int main()
{
    int heap[] = {0, 17, 26, 45, 14, 32, 22, 10};
    HeapSort(heap, 7);

    for(int i = 7; i >= 1; --i)
    {
        printf("%d\n", heap[i]);
    }
    return 0;
}
