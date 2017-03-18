#include <stdio.h>
#include <stdlib.h>


void Merge(int list[], int tmp[], int l_pos, int r_pos, int r_end)
{
    int l_end, len, tmp_pos;

    l_end = r_pos - 1;
    tmp_pos = l_pos;
    len = r_end - l_pos + 1;

    while(l_pos <= l_end && r_pos <= r_end)
    {
        if(list[l_pos] <= list[r_pos])
        {
            tmp[tmp_pos++] = list[l_pos++];
        }
        else
        {
            tmp[tmp_pos++] = list[r_pos++];
        }
    }

    while(l_pos <= l_end)
    {
        tmp[tmp_pos++] = list[l_pos++];
    }
    while(r_pos <= r_end)
    {
        tmp[tmp_pos++] = list[r_pos++];
    }

    for(int i = 0; i < len; ++i, --r_end)
    {
        list[r_end] = tmp[r_end];
    }
}


void MSort(int list[], int tmp[], int left, int right)
{
    int center;

    if(left < right)
    {
        center = (left + right) / 2;
        MSort(list, tmp, left, center);
        MSort(list, tmp, center + 1, right);
        Merge(list, tmp, left, center+1, right);
    }
}


void MergeSort(int list[], int len)
{
    int *tmp;
    tmp = malloc(sizeof(int) * len);
    MSort(list, tmp, 0, len - 1);
    free(tmp);
}



int main()
{
    int list[] = {1, 4, 10, 22, 3, 2};
    MergeSort(list, 6);

    for(int i = 0; i < 6; ++i)
    {
        printf("%d\n", list[i]);
    }
    return 0;
}
