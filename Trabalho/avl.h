#pragma once

#include <stdlib.h>
#include <stdio.h>

struct s_node {
	void* info;
	int balanceFactor;
	struct s_node* left;
	struct s_node* right;
};

typedef struct s_node AVLNode;

void CenteredRight(AVLNode* tree, void (*printFunction)(void*));

AVLNode* AVLInitialize();

AVLNode* AVLInsert(AVLNode* tree, void* data, int* ok, int (*compareFuntion)(void*, void*));

AVLNode* AVLUnbalancedLeft(AVLNode* tree, int* ok);

AVLNode* AVLUnbalancedRight(AVLNode* tree, int* ok);

AVLNode* AVLRotateRight(AVLNode* tree);

AVLNode* AVLRotateLeft(AVLNode* tree);

AVLNode* AVLRotateLeftRight(AVLNode* tree);

AVLNode* AVLRotateRightLeft(AVLNode* tree);

AVLNode* AVLFind(AVLNode* tree, void* data, int (*compareFuntion)(void*, void*));

AVLNode* AVLNNodeCenteredRight(AVLNode* tree, int n, int* actual);