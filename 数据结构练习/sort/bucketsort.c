#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// It be used to sort the simple and non repeating array.
void BucketSort(int list[], int len)
{
    int max = 0, i, j;
    int *bucket;
    for(i = 0; i < len; ++i)
    {
        max = list[i] > max ? list[i] : max;
    }

    bucket = malloc(sizeof(int) * max);
    memset(bucket, 0, sizeof(int) * max);

    for(i = 0; i < len; ++i)
    {
        bucket[list[i] - 1] = list[i];
    }

    j = 0;
    while(max > 0)
    {
        if(bucket[--max] != 0)
        {
            list[j++] = bucket[max];
        }
    }

    free(bucket);
}

int main()
{
    int list[] = {10, 20, 4, 5, 3, 2};

    BucketSort(list, 6);

    for(int i = 0; i < 6; ++i)
    {
        printf("%d ", list[i]);
    }
    puts("");

    return 0;
}
