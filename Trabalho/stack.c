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

Stack* StackFind(Stack* stack, void* data, int(*compareFuntion)(void*, void*))
{
	Stack* aux;

	if (stack) {
		for (aux = stack; aux != NULL; aux = aux->top)
			if ((*compareFuntion)(aux->data, data) == 0)
				return aux;
	}

	return NULL;
}
