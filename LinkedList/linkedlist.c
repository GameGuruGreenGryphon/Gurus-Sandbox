#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node* next;
};

#define MAXLIST 100
char ENDLIST = '\0';
char STARTLIST = ~0;

struct node* MakeNode(struct node* next, char data) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = next;
	return newNode;
}

struct node* InitList() {
	struct node* tail = MakeNode(NULL, ENDLIST);
	struct node* head = MakeNode(tail, STARTLIST);
	return head;
}

int iter = 0;

void PrintList(struct node* node) {
	if (node->data != STARTLIST) {
		printf("[%d]: %c\n", iter++, node->data);
	}

	if (node->next->data != ENDLIST) {
		PrintList(node->next);
	} else {
		iter = 0;
	}
}

// The true last node is the terminator node, which points to null
// Deltas below 0 will traverse the nodes until the terminator is found
// Deltas above 0 will traverse until it finds the node past delta
struct node* FindNode(struct node* startNode, int delta) {

	int count = 0;
	struct node* node = startNode;

	if (delta < 0) {
		// Find penultimate list item
		while (node->next->data != ENDLIST && count++ < MAXLIST) {
			node = node->next;
		}
	} else {
		// Find list terminator
		while (node->data != ENDLIST && delta-- != 0 && count++ < MAXLIST) {
			node = node->next;
		}
	}
	return node;
}

//
int DeleteNextNode(struct node* node, int delta) {
	struct node* nextNode = FindNode(node, delta);
	if (nextNode->data == ENDLIST) {
		printf("Fail 1");
		return 0;
	}

	struct node* afterThat = FindNode(nextNode, 1);

	node->next = afterThat;

	free(nextNode);
	
	return 1;
}

void FreeList(struct node* head) {

	struct node* reaper = head;

	while (1) {
		struct node* nextNode = FindNode(reaper, 1);
		free(reaper);
		if (reaper == nextNode) {
			break;
		}
		reaper = nextNode;
	}
}

struct node* InsertNode(struct node* startNode, char data, int delta) {
	struct node* pen = FindNode(startNode, delta);
	if (pen) {
		return pen->next = MakeNode(pen->next, data);
	} else {
		return pen;
	}
}

int main() {
	struct node* head = InitList();
	PrintList(head);
	printf("\n");

	InsertNode(head, 'h', -1);
	PrintList(head);
	printf("\n");

	for (int i = 0; i < 10; i++) {
		InsertNode(head, 'e', -1);
	}

	PrintList(head);
	printf("\n");

	InsertNode(head, 'o', 2);
	InsertNode(head, 'l', 2);
	InsertNode(head, 'l', 2);
	PrintList(head);
	printf("\n");
	
	printf("Testing DeleteNextNode()");
	DeleteNextNode(head, -1);
	PrintList(head);
	printf("\n");

	printf("Testing DeleteNextNode()");
	DeleteNextNode(head, -1);
	PrintList(head);

	FreeList(head);
}
