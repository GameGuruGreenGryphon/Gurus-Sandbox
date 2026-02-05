#include <stdio.h>
#include <stdlib.h>

#define MAXLIST 127

struct node {
	int data;
	struct node* left;
	struct node* right;
};

struct node* MakeNode(struct node* left, struct node* right, int data) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->left = left;
	newNode->right = right;
	return newNode;
}

void PrintNode(struct node* node, char* name) {
	printf("[%s]\tdata: %3d\taddress: %14p\tleft: %14p\t right: %14p\n", name, node->data, node, node->left, node->right);
}

void PrintTree(struct node* node) {
	if (node) {
		PrintNode(node, "PrintList");
		PrintTree(node->left);
		PrintTree(node->right);
	}
}

void FreeTree(struct node* node) {
	if (node) {
		FreeTree(node->left);
		FreeTree(node->right);
		free(node);
	}
}

struct node* InsertNode(struct node* root, int data) {
	struct node* node = root;
	struct node* prevNode = node;
	while (node) {
		prevNode = node;
		if (data > node->data) {
			node = node->right;
		} else {
			node = node->left;
		}
	}

	if (data > prevNode->data) {
		return prevNode->right = MakeNode(NULL, NULL, data);
	} else {
		return prevNode->left = MakeNode(NULL, NULL, data);
	}

}

int main() {
	struct node* root = MakeNode(NULL, NULL, MAXLIST / 2);
	PrintTree(root);
	printf("\n");

	InsertNode(root, 5);
	PrintTree(root);
	printf("\n");

	InsertNode(root, 10);
	InsertNode(root, 37);
	InsertNode(root, 100);
	InsertNode(root, 1);
	InsertNode(root, 4);
	InsertNode(root, 8);
	InsertNode(root, 16);
	InsertNode(root, 32);
	InsertNode(root, 64);
	PrintTree(root);
	printf("\n");

	FreeTree(root);
}
