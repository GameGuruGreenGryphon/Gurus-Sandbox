#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node* left;
	struct node* right;
};

struct node* MakeNode(struct node* left, struct node* right, char data) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->left = left;
	newNode->right = right;
	return newNode;
}

void PrintNode(struct node* node, char* name) {
	printf("[%s]\tdata: %c\taddress: %p\tleft: %p\n right: %p", name, node->data, node, node->left, node->right);
}

void PrintList(struct node* node) {
	while (node) {
		PrintNode(node, "PrintList");
		PrintList(node->left);
		PrintList(node->right);
	}
}

void FreeTree(struct node* node) {
}


int main() {
	struct node* root = MakeNode(NULL, NULL, '\0');
}
