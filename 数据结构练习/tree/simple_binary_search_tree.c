#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
    int unit;
    struct node *left;
    struct node *right;
};

typedef struct node *Position;
typedef struct node *SearchTree;


// Empty the tree.
SearchTree MakeEmpty(SearchTree tree)
{
    if(tree != NULL)
    {
        MakeEmpty(tree->left);
        MakeEmpty(tree->right);
        free(tree);
    }
    return NULL;
}


// Find the position of the unit.
Position Find(SearchTree tree, int unit)
{
    if(tree == NULL)
    {
        return NULL;
    }
    if(unit < tree->unit)
    {
        return Find(tree->left, unit);
    }
    else if(unit > tree->unit)
    {
        return Find(tree->right, unit);
    }
    else
    {
        return tree;
    }
}


// Find the position of the minimum unit.
Position FindMin(SearchTree tree)
{
    if(tree == NULL)
        return NULL;
    else
    {
        if(tree->left == NULL)
        {
            return tree;
        }
        else
        {
            return FindMin(tree->left);
        }
    }
}


// Find the position of the maximum unit.
Position FindMax(SearchTree tree)
{
    if(tree != NULL)
    {
        while( tree->right != NULL)
        {
            tree = tree->right;
        }
    }
    return tree;
}


// Insert the unit into search tree.
SearchTree Insert(SearchTree tree, int unit)
{
    if(tree == NULL)
    {
        tree = malloc(sizeof(Position));
        tree->unit = unit;
        tree->left = tree->right = NULL;
    }
    else
    {
        if( unit < tree->unit)
        {
            tree->left = Insert(tree->left, unit);
        }
        else if(unit > tree->unit)
        {
            tree->right = Insert(tree->right, unit);
        }
    }

    return tree;
}


// Delete the position of the unit.
SearchTree Delete(SearchTree tree, int unit)
{
    if(tree == NULL)
    {
        return NULL;
    }
    else
    {
        if( unit < tree->unit)
        {
            tree->left = Delete(tree->left, unit);
        }
        else if(unit > tree->unit)
        {
            tree->right = Delete(tree->right, unit);
        }
        else
        {
            Position tmp;
            if(tree->left && tree->right)
            {
                tmp = FindMin(tree->right);
                tree->unit = tmp->unit;
                tree->right = Delete(tree->right, tree->unit);
            }
            else
            {
                tmp = tree;
                if(tree->left == NULL)
                {
                    tree = tree->right;
                }
                else if(tree->right == NULL)
                {
                    tree = tree->left;
                }
                free(tmp);
            }
        }
    }
    return tree;
}


// Print the search tree.
void PrintTree(SearchTree tree, int depth)
{
    if(tree != NULL)
    {
        for(int i = 0; i < depth; ++i)
        {
            printf("--");
        }
        printf("%d\n", tree->unit);
        PrintTree(tree->left, depth + 1);
        PrintTree(tree->right, depth + 1);
    }
}


int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        SearchTree tree;

        for(int i = 1; i < argc; ++i)
        {
            tree = Insert(tree, atoi(argv[i]));
        }

        PrintTree(tree, 0);

        printf("Find the minimum unit:%d\n", FindMin(tree)->unit);
        printf("Find the maximum unit:%d\n", FindMax(tree)->unit);

        tree = Delete(tree, FindMin(tree)->unit);
        puts("Delete the minimum.");
        printf("Find the minimum unit:%d\n", FindMin(tree)->unit);

        PrintTree(tree, 0);

        tree = MakeEmpty(tree);
    }
    else
    {
        printf("Please enter some number.\n");
        printf("Like this:\n");
        printf("./a.out 5 1 6 0 3\n");
    }

    return 0;
}
