#include "stack.h"

Stack* StackInitialize()
{
	return NULL;
}

Stack* StackPush(Stack* stack, void* data)
{
	Stack* node = (Stack*)malloc(sizeof(Stack));

	node->data = data;

	node->top = stack;

	return node;
}
