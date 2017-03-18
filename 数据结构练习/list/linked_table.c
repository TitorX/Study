#include <stdio.h>
#include <stdlib.h>

struct node{
    int unit;
    struct node *next;
};

typedef struct node *Node;
typedef struct node *List;


List MakeEmpty()
{
    List list = malloc(sizeof(struct node));
    list->next = NULL;
    return list;
}


int IsEmpty(List list)
{
    if(list->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int IsLast(Node node)
{
    return node->next == NULL;
}


Node Find(List list, int unit)
{
    Node tmp;
    tmp = list->next;
    while(tmp != NULL && tmp->unit !=unit)
    {
        tmp = tmp->next;
    }
    return tmp;
}


Node FindPrevious(List list, int unit)
{
    Node tmp;

    tmp = list;
    while(tmp->next != NULL && tmp->next->unit != unit)
    {
        tmp = tmp->next;
    }
    return tmp;
}


void Delete(List list, int unit)
{
    Node pre, tmp;
    pre = FindPrevious(list, unit);

    if(!IsLast(pre))
    {
        tmp = pre->next;
        pre->next = tmp->next;
        free(tmp);
    }
}


void Insert(List list, int index, int unit)
{
    Node node, tmp;
    node = malloc(sizeof(struct node));
    node->unit = unit;

    tmp = list;

    for(int i = 0; i < index - 1; ++i)
    {
        if(tmp != NULL)
        {
            tmp = tmp->next;
        }
        else
        {
            break;
        }
    }

    if(tmp != NULL)
    {
        node->next = tmp->next;
        tmp->next = node;
    }

}


void DeleteList(List list)
{
    Node node, tmp;

    node = list->next;

    while(node != NULL)
    {
        tmp = node->next;
        free(node);
        node = tmp;
    }
}


int main()
{
    List list;
    list = MakeEmpty();

    if(IsEmpty(list))
    {
        puts("Is empty!");
    }
    else
    {
        puts("Isn't empty!");
    }

    Insert(list, 0, 10);

    printf("Find %d\n", Find(list, 10)->unit);

    Delete(list, 10);

    if(Find(list, 10))
    {
        puts("Find it.");
    }
    else
    {
        puts("Not");
    }

    DeleteList(list);

    return 0;
}
