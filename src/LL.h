#pragma once
#include <stdio.h>

typedef struct node {
	void* value;
	struct node* next;
} node;

typedef struct linkedList {
	node* head;
} linkedList;

void initLL(linkedList* linkedList, void* value);

void insertLL(linkedList* LinkedList, int index, void* value);
void removeLL(linkedList* linkedList, int index);
void appendLL(linkedList* linkedList, void* value);
void prependLL(linkedList* linkedList, void* value);

void destroyLL(linkedList* linkedList);

// for debugging only, requires changing the typecast to
// whatever the LL is storing
void printLL(linkedList* linkedList); 
