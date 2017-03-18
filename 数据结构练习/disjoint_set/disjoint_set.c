/*
    Achieve disjoint set with the improved method.
*/
#include <stdio.h>
#include <stdlib.h>

#define NUMSETS 10

typedef int DisjSet[NUMSETS + 1];
typedef int SetType;


void Initialize(DisjSet S)
{
    for(int i = NUMSETS; i > 0; --i)
    {
        S[i] = 0;
    }
}


// Union element according to the depth.
void SetUnion(DisjSet S, SetType root1, SetType root2)
{
    if(S[root2] < S[root1])
    {// Root2 is deeper set.
        S[root1] = root2;  // Make root2 new root;
    }
    else
    {
        if(S[root1] == S[root2])
        {
            --S[root1];
        }
        S[root2] = root1;
    }
}


// Path compression.
SetType Find(SetType x, DisjSet S)
{
    if(S[x] <= 0)
    {
        return x;
    }
    else
    {
        return S[x] = Find(S[x], S);
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

    for(int i = 1; i <= NUMSETS; ++i)
    {
        printf("%d\n", Find(i, S));
    }

    return 0;
}
