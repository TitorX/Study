#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 20

struct node{
    int unit;
    struct node *next;
};

typedef struct node *Node;

struct tab{
    int table_size;
    Node *list;
};

typedef struct tab *HashTable;


HashTable InitializeTable(int size)
{
    HashTable table;

    table = malloc(sizeof(struct tab));
    table->table_size = size;

    table->list = malloc(sizeof(Node) * table->table_size);

    for(int i = 0; i < table->table_size; ++i)
    {
        table->list[i] = malloc(sizeof(struct node));
        table->list[i]->next = NULL;
    }

    return table;
}


void DestoryTable(HashTable table)
{
    void FreeNode(Node node)
    {
        if(node != NULL)
        {
            if(node->next != NULL)
            {
                FreeNode(node->next);
            }

            free(node);
        }
    }

    for(int i = 0; i < table->table_size; ++i)
    {
        FreeNode(table->list[i]);
    }
    free(table->list);
    free(table);
}


int Hash(int key, int table_size)
{
    return key % table_size;
}


Node Find(HashTable table, int key)
{
    Node tmp;

    tmp = table->list[Hash(key, table->table_size)]->next;

    if(tmp != NULL)
    {
        while(tmp->unit != key)
        {
            if(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            else
            {
                return NULL;
            }
        }
    }

    return tmp;
}


void Insert(HashTable table, int key)
{
    if(Find(table, key) == NULL)
    {
        Node new_node = malloc(sizeof(struct node));
        new_node->unit = key;

        Node list = table->list[Hash(key, table->table_size)];

        new_node->next = list->next;
        list->next = new_node;
    }
}


int main()
{
    HashTable table;

    table = InitializeTable(1000);


    Node tmp;
    Insert(table, 110);
    tmp = Find(table, 110);
    if(tmp == NULL)
    {
        puts("None!");
    }
    else
    {
        puts("Find it!!!");
    }

    DestoryTable(table);
    return 0;
}
