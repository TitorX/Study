/*
	This is a simple code written in C language for practising the usage of stack.
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
	int num;
	struct node * next;
};

typedef struct node Node;  // stack node
typedef struct node * Stack;  // stack header


// Build a header of the stack.
Stack BuildStack()
{
	Stack stack;
	stack = malloc(sizeof(Node));
	stack->next = NULL;
	return stack;
}


//Push an element into the stack.
void Push(Stack stack, int num)
{
	Node *new = malloc(sizeof(Node));
	new->num = num;
	new->next = stack->next;
	stack->next = new;
}


//Pop an element from the stack.
void Pop(Stack stack)
{
	if(stack->next != NULL)
	{
		Node *last;
		last = stack->next;
		stack->next = stack->next->next;
		free(last);
	}
}


//Pop all elements from the stack.
void Clear(Stack stack)
{
	while(stack->next != NULL)
	{
		Pop(stack);
	}
}


int main()
{
	Stack stack = BuildStack();

	for(int i = 0; i < 5; ++i)
	{
		printf("Push %d\n", i);
		Push(stack, i);
	}

	while(stack->next!=NULL)
	{
		printf("num is: %d\n", stack->next->num);
		Pop(stack);
	}

	free(stack);
	return 0;
}

