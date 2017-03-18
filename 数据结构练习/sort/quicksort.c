#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define CUTOFF 3

void QSort(int list[], int left, int right)
{
    int tmp, l_pos, r_pos, pivot, c_pos;

    if(left + CUTOFF <= right)
    {// When the unit number of the subarray is large enough, do a quick sort on the subarray.
        c_pos = (left + right) / 2;
        pivot = list[c_pos];

        tmp = list[c_pos];
        list[c_pos] = list[right];
        list[right] = tmp;

        l_pos = left, r_pos = right - 1;

        l_pos -= 1, r_pos += 1;
        for (;;)
        {
            while(list[++l_pos] < pivot){}
            while(list[--r_pos] > pivot){}

            if (l_pos < r_pos)
            {
                tmp = list[l_pos];
                list[l_pos] = list[r_pos];
                list[r_pos] = tmp;
            }
            else
            {
                break;
            }
        }
        tmp = list[l_pos];
        list[l_pos] = list[right];
        list[right] = list[l_pos];

        QSort(list, left, l_pos - 1);
        QSort(list, l_pos + 1, right);
    }
    else
    {// When the unit number of the subarray is too small, do an insertion sort on the subarray.
        for (int i = left + 1; i <= right; ++i)
        {
            tmp = list[i];
            for(l_pos = i; l_pos > 0 && list[l_pos - 1] > tmp; --l_pos)
            {
                list[l_pos] = list[l_pos - 1];
            }
            list[l_pos] = tmp;
        }
    }
}


void QuickSort(int list[], int len)
{
    QSort(list, 0, len-1);
}


int main()
{
    int list[MAX];

    for(int i = 0; i < MAX; ++i)
    {
        list[i] = random()%1000;
    }

    QuickSort(list, MAX);

    for(int i = 0; i < MAX; ++i)
    {
        printf("%d\n", list[i]);
    }

    return 0;
}
