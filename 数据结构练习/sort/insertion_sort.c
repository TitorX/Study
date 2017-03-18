#include <stdio.h>
#include <stdlib.h>


void InsertionSort(int list[], int len)
{
    int node, pre;
    int tmp;
    for(node = 1; node < len; ++node)
    {
        tmp = list[node];
        for(pre = node; pre > 0 && list[pre - 1] > tmp; --pre)
        {
            list[pre] = list[pre - 1];
        }
        list[pre] = tmp;
    }
}


int main()
{
    int list[] = {10, 7, 4, 2, 15, 29};

    InsertionSort(list, 6);

    for(int i = 0; i < 6; ++i)
    {
        printf("%d ", list[i]);
    }
    puts("");

    return 0;
}
