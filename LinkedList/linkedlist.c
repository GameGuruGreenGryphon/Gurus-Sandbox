#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node* next;
};

#define MAXLIST 100

struct node* MakeNode(struct node* next, char data) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = next;
	return newNode;
}

void PrintNode(struct node* node, char* name) {
	printf("[%s]\tdata: %c\taddress: %p\tnext: %p\n", name, node->data, node, node->next);
}

void PrintList(struct node* node) {
	while (node) {
		PrintNode(node, "PrintList");
		node = node->next;
	}
}

int CountNodes(struct node* node) {
	int count = 0;
	while (node && count++ < MAXLIST) {
		node = node->next;
	}
	return count;
}

// Deltas below 0 will traverse the nodes until a node that leads to NULL is found
// Deltas above 0 will traverse until it finds the node past delta
struct node* FindNode(struct node* node, int delta) {
	int count = 0;

	if (node == NULL) {
		return NULL;
	}

	if (delta < 0) {
		delta = CountNodes(node);
	}

	while (node->next && count++ < delta) {
		node = node->next;
	}

	return node;
}

int DeleteNextNode(struct node* node, int delta) {

	if (delta < 0) {
		delta = CountNodes(node);
		delta -= 2;
	}

	node = FindNode(node, delta);

	if (node->next) {
		struct node* todie = node->next;
		node->next = node->next->next;
		free(todie);

		return 1;
	} else {
		return 0;
	}
}

void FreeList(struct node* node) {
	int count = 0;

	while (node) {
		if (count++ > MAXLIST) {
			exit(1);
		}

		struct node* nextNode = node->next;
		free(node);
		node = nextNode;
	}
}

struct node* InsertNode(struct node* node, char data, int delta) {
	if (node == NULL) {
		return NULL;
	}
	
	node = FindNode(node, delta);

	return node->next = MakeNode(node->next, data);
}

int main() {
	printf("Making head\n");
	struct node* head = MakeNode(NULL, 0);
	printf("Result:\n");
	PrintList(head);
	printf("\n");

	printf("Inserting 'h'\n");
	InsertNode(head, 'h', -1);
	printf("Result:\n");
	PrintList(head);
	printf("\n");

	printf("Inserting many 'e'\n");
	for (int i = 0; i < 10; i++) {
		InsertNode(head, 'e', -1);
	}

	printf("Result:\n");
	PrintList(head);
	printf("\n");

	printf("Inserting familiar chars\n");
	InsertNode(head, 'o', 2);
	InsertNode(head, 'l', 2);
	InsertNode(head, 'l', 2);
	printf("Result:\n");
	PrintList(head);
	printf("\n");
	
	printf("Testing DeleteNextNode()\n");
	DeleteNextNode(head, 5);
	printf("Result:\n");
	PrintList(head);
	printf("\n");

	printf("Testing DeleteNextNode()\n");
	DeleteNextNode(head, -1);
	printf("Result:\n");
	PrintList(head);

	FreeList(head);
}
