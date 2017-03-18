#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char unit;
    struct node *next;
};

typedef struct node *Node;  // stack node
typedef struct node *Stack;  // stack header


// Build a header of the stack.
Stack BuildStack()
{
	Stack stack;
	stack = malloc(sizeof(Node));
	stack->next = NULL;
	return stack;
}


// Push an element of the stack.
void Push(Stack stack, char unit)
{
	Node new = malloc(sizeof(Node));
	new->unit = unit;
	new->next = stack->next;
	stack->next = new;
}


// Pop an element from the stack.
void Pop(Stack stack)
{
	if(stack->next != NULL)
	{
		Node last;
		last = stack->next;
		stack->next = stack->next->next;
		free(last);
	}
}


// Pop all elements from the stack.
void Clear(Stack stack)
{
	while(stack->next != NULL)
	{
		Pop(stack);
	}
}


// Check the stack whether is empty.
int IsEmpty(Stack stack)
{
    if(stack->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// Obtain the top element of the stack.
char Top(Stack stack)
{
    if(!IsEmpty(stack))
    {
        return stack->next->unit;
    }
    else
    {
        return 0;
    }
}


// Judge whether the symbol in text is balanced.
int balance_symbol(char text[])
{
    Stack stack;
    stack = BuildStack();

    for(int i = 0; i < strlen(text); ++i)
    {
        switch(text[i])
        {
            case '(':
            case '{':
            case '[':
                {
                    Push(stack, text[i]);
                    break;
                }


            case ')':
                {
                    if(Top(stack) == '(')
                    {
                        Pop(stack);
                        break;
                    }
                    else
                    {
                        return 0;
                    }
                }
            case '}':
                {
                    if(Top(stack) == '{')
                    {
                        Pop(stack);
                        break;
                    }
                    else
                    {
                        return 0;
                    }
                }
            case ']':
                {
                    if(Top(stack) == '[')
                    {
                        Pop(stack);
                        break;
                    }
                    else
                    {
                        return 0;
                    }
                }
        }
    }

    if(IsEmpty(stack))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

