#include "avl.h"

// Imprime a AVL usando o caminhamento central a esquerda
void CenteredRight(AVLNode* tree, void (*printFunction)(void*)) {
	if (tree != NULL) {
		CenteredRight(tree->right, *printFunction);
		(*printFunction)(tree->info);
		CenteredRight(tree->left, *printFunction);
	}
}

// Inicializa a AVL
AVLNode* AVLInitialize() {
	return NULL;
}

// Insere um novo nodo na AVL
AVLNode* AVLInsert(AVLNode* tree, void* data, int* ok, int (*compareFuntion)(void*, void*)) {
	if (tree == NULL) {
		tree = (AVLNode*)malloc(sizeof(AVLNode));

		tree->info = data;

		tree->left = NULL;
		tree->right = NULL;

		tree->balanceFactor = 0;

		*ok = 1;
	}
	else {
		if ((*compareFuntion)(data, tree->info) < 0) {
			tree->left = AVLInsert(tree->left, data, ok ,(*compareFuntion));
			if (*ok) {
				switch (tree->balanceFactor) {
				case -1:
					tree->balanceFactor = 0;
					*ok = 0;
					break;
				case 0:
					tree->balanceFactor = 1;
					break;
				case 1:
					tree = AVLUnbalancedLeft(tree, ok);
					break;
				}
			}
		}
		else {
			tree->right = AVLInsert(tree->right, data, ok, (*compareFuntion));
			if (*ok) {
				switch (tree->balanceFactor) {
				case 1:
					tree->balanceFactor = 0;
					*ok = 0;
					break;
				case 0:
					tree->balanceFactor = 1;
					break;
				case -1:
					tree = AVLUnbalancedRight(tree, ok);
					break;
				}
			}
		}
	}

	return tree;
}

// Função para rotações
AVLNode* AVLUnbalancedLeft(AVLNode* tree, int* ok) {
	AVLNode* node;

	node = tree->left;

	if (node->balanceFactor == 1)
		tree = AVLRotateRight(tree);
	else
		tree = AVLRotateLeftRight(tree);

	tree->balanceFactor = 0;
	*ok = 0;

	return tree;
}

// Função para rotações
AVLNode* AVLUnbalancedRight(AVLNode* tree, int* ok) {
	AVLNode* node;

	node = tree->right;

	if (node->balanceFactor == -1)
		tree = AVLRotateLeft(tree);
	else
		tree = AVLRotateRightLeft(tree);

	tree->balanceFactor = 0;
	*ok = 0;

	return tree;
}

// Rotação a diretira
AVLNode* AVLRotateRight(AVLNode* tree) {
	AVLNode* node;

	node = tree->left;
	tree->left = node->right;
	node->right = tree;

	tree->balanceFactor = 0;

	tree = node;

	return tree;
}

// Rotação a esquerda
AVLNode* AVLRotateLeft(AVLNode* tree) {
	AVLNode* node;

	node = tree->right;
	tree->right = node->left;
	node->left = tree;

	tree->balanceFactor = 0;

	tree = node;

	return tree;
}

// Rotação dupla a diretira
AVLNode* AVLRotateLeftRight(AVLNode* tree) {
	AVLNode* node1, * node2;

	node1 = tree->left;
	node2 = node1->right;

	if (!node1 || !node2) {
		return tree;
	}

	node1->right = node2->left;
	node2->left = node1;
	tree->left = node2->right;
	node2->right = tree;

	if (node2->balanceFactor == 1)
		tree->balanceFactor = -1;
	else
		tree->balanceFactor = 0;

	if (node2->balanceFactor == -1)
		node1->balanceFactor = 1;
	else
		node1->balanceFactor = 0;

	tree = node2;

	return tree;
}

// Rotação dupla a esquerda
AVLNode* AVLRotateRightLeft(AVLNode* tree) {
	AVLNode* node1, * node2;

	node1 = tree->right;
	node2 = node1->left;

	node1->left = node2->right;
	node2->right = node1;
	tree->right = node2->left;
	node2->left = tree;

	if (node2->balanceFactor == 1)
		tree->balanceFactor = -1;
	else
		tree->balanceFactor = 0;

	if (node2->balanceFactor == -1)
		node1->balanceFactor = 1;
	else
		node1->balanceFactor = 0;

	tree = node2;

	return tree;
}

// Função que procura um elemento dentro da árvore
AVLNode* AVLFind(AVLNode* tree, void* data, int (*compareFuntion)(void*, void*))
{
	if (tree == NULL) {
		return NULL;
	}
	else {
		if ((*compareFuntion)(data, tree->info) == 0)
			return tree;
		else {
			AVLNode* found = AVLFind(tree->left, data, *compareFuntion);
			if (!found)
				return AVLFind(tree->right, data, *compareFuntion);
		}
	}

	return NULL;
}

// Função que retorna o n-ésimo elemento da árvore no caminhamento central a esquerda
AVLNode* AVLNNodeCenteredRight(AVLNode* tree, int n, int* actual) {
	AVLNode* node = NULL;

	if (tree != NULL && *actual <= n) {
		node = AVLNNodeCenteredRight(tree->right, n, actual);

		if (node != NULL)
			return node;

		(*actual)++;

		if (*actual == n)
			return tree;

		node = AVLNNodeCenteredRight(tree->left, n, actual);
	}

	return node;
}