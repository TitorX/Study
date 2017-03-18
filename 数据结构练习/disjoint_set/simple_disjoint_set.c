/*
    Achieve disjoint set with simplest method.
*/
#include <stdio.h>
#include <stdlib.h>

#define NUMSETS 20

typedef int DisjSet[NUMSETS];
typedef int SetType;


void Initialize(DisjSet S)
{
    for(int i = NUMSETS; i > 0; --i)
    {
        S[i] = 0;
    }
}


void SetUnion(DisjSet S, SetType root1, SetType root2)
{
    S[root2] = root1;
}


SetType Find(SetType x, DisjSet S)
{
    if(S[x] <= 0)
    {
        return x;
    }
    else
    {
        return Find(S[x], S);
    }
}


int main()
{
    DisjSet S;

    Initialize(S);

    SetType r1, r2;
    r1 = Find(1, S);
    r2 = Find(3, S);
    if(r1 && r2 && r1 == r2)
    {
        puts("1 and 3 are in the same set.");
    }
    else
    {
        puts("1 and 3 are in different set.");
    }

    SetUnion(S, 1, 3);

    r1 = Find(1, S);
    r2 = Find(3, S);
    if(r1 && r2 && r1 == r2)
    {
        puts("1 and 3 are in the same set.");
    }
    else
    {
        puts("1 and 3 are in different set.");
    }

    return 0;
}
