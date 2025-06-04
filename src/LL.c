#include <stdio.h>
#include <stdlib.h>

#include "LL.h"

// this should all be working hopefully if it doesnt ill just
// just delete it hahahah jk jk or am i?????

static node* createNode(void* value, node* next) {
	node* newNode = malloc(sizeof(node));
	if(!newNode) {
		printf("malloc failed to create node\n");
		return NULL;
	}
	newNode->value = value;
	newNode->next = next;
	return newNode;
}

void initLL(linkedList* linkedList, void* value) {
	node* head = malloc(sizeof(node));
	if(!head) {
		printf("malloc failed\n");
		return;
	}
	head->value = value;
	head->next = NULL;
	
	linkedList->head = head;
}

void insertLL(linkedList* linkedList, int index, void* value) {
	node* newNode = createNode(value, NULL);

	uint currentIndex = 0;
	node* previousNode = NULL;
	node* currentNode = linkedList->head;

	if(index == 0) {
		newNode->next = linkedList->head;
		linkedList->head = newNode;
		return;
	}

	while(currentNode != NULL) {
		if(currentIndex == index) {
			previousNode->next = newNode;
			newNode->next = currentNode;
			return;
		}

		previousNode = currentNode;
		currentNode = currentNode->next;
		currentIndex++;
	}
	
	printf("tried to insert out of linkedlist bounds, size is %d\n",
			currentIndex);
}

void removeLL(linkedList* linkedList, int index) {
	uint currentIndex = 0;
	node* currentNode = linkedList->head;
	node* previousNode = NULL;

	if(index == 0) {
		currentNode = currentNode->next;
		linkedList->head = NULL;
		free(linkedList->head);
		linkedList->head = currentNode;
		return;
	}

	while(currentNode) {
		if(currentIndex == index) { 
			previousNode->next = currentNode->next;
			free(currentNode);
			return;
		} else if(!currentNode->next) {
			return;
		}

		previousNode = currentNode;
		currentNode = currentNode->next;
		currentIndex += 1;
	}
}
void appendLL(linkedList* linkedList, void* value) {
	node* newNode = createNode(value, NULL);

	node* currentNode = linkedList->head;
	while(currentNode->next != NULL) {
		currentNode = currentNode->next;
	}
	currentNode->next = newNode;
}

void prependLL(linkedList* linkedList, void* value) {
	node* newNode = createNode(value, linkedList->head);	

	linkedList->head = newNode;
}

void destroyLL(linkedList* linkedList) {
	node* currentNode = linkedList->head;
	node* previousNode = NULL;

	while(currentNode) {
		previousNode = currentNode;
		currentNode = currentNode->next;
		free(previousNode->value);
		free(previousNode);
	}
}

void printLL(linkedList* linkedList) {
	node* currentNode = linkedList->head;
	while(currentNode) {
		printf("%d, ", *(int*)currentNode->value);
		currentNode = currentNode->next;
	}
	printf("\n");
}
