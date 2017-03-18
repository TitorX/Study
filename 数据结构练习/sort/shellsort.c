#include <stdio.h>
#include <stdlib.h>


void ShellSort(int l[], int len)
{
    int i, j, increment;
    int tmp;

    for(increment = len/2; increment > 0; increment /=2)
    {
        for(i = increment; i < len; ++i)
        {
            tmp = l[i];
            for(j = i; j >= increment; j -= increment)
            {
                if(tmp < l[j - increment])
                {
                    l[j] = l[j - increment];
                }
                else
                {
                    break;
                }
            }
            l[j] = tmp;
        }
    }
}


int main()
{
    int l[] = {1, 10, 22, 33, 2, 0, 5};

    ShellSort(l, 7);

    for(int i = 0; i < 7; ++i)
    {
        printf("%d ", l[i]);
    }
    puts("");

    return 0;
}
