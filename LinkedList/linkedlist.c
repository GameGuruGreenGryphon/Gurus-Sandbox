#include <stdio.h>
#include <stdlib.h>

struct node {
	char data;
	struct node* next;
};

#define MAXLIST 100
char ENDLIST = '\0';

struct node* MakeNode(struct node* next, char data) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = next;
	return newNode;
}

struct node* InitList(char data) {
	struct node* tail = MakeNode(NULL, '\0');
	struct node* head = MakeNode(tail, data);
	return head;
}

int iter = 0;

void PrintList(struct node* node) {
	printf("[%d]: %c", iter++, node->data);
	if (node->data != '\0') {
		PrintList(node->next);
	}
}

// Traverse list until we find penultimate node
// The true last node is the terminator node, which points to null
// Deltas below 0 will traverse the nodes until the terminator is found
// Deltas above 0 will traverse until it finds the node past delta
struct node* FindNode(struct node* startNode, int delta) {

	int count = 0;
	struct node* pen = startNode;
	while (pen->next->data != '\0' && delta-- != 0) {
		pen = startNode->next;

		if (count++ > MAXLIST) {
			return NULL;
		}
	}
	return pen;
}

void DeleteNextNode(struct node* prevNode) {
	struct node* nextNode = FindNode(prevNode, 1);
	struct node* afterThat = FindNode(nextNode, 1);

	prevNode->next = afterThat;

	free(nextNode);
}

void FreeList(struct node* head) {

	struct node* reaper = head;

	while (1) {
		struct node* nextNode = FindNode(reaper, 1);
		// nextNode returns itself if the next node is the terminator
		if (reaper == nextNode) {
			// free terminator
			free(reaper->next);
			// free the reaper
			free(reaper);
			break;
		}

		free(reaper);
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
	struct node* head = InitList('h');

	for (int i = 0; i < 10; i++) {
		InsertNode(head, 'e', -1);
	}

	InsertNode(head, 'l', 5);
	InsertNode(head, 'l', 5);

	PrintList(head);

	FreeList(head);
}
