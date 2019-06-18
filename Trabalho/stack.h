#pragma once

#include <stdlib.h>

struct s_stack {
	void* data;
	struct s_stack* top;
};

typedef struct s_stack Stack;

Stack* StackInitialize();

Stack* StackPush(Stack* stack, void* data);