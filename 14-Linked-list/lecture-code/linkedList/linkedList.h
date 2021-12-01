#pragma once

#include <stdio.h>

struct Node
{
	int value;
	struct Node* next;
};

typedef struct Node node;

struct List
{
	node* head;
	node* tail;
	size_t size;
};

typedef struct List list;

list* createList();
void pushBack(list*, int);
void addRandom(list*, size_t);
int popBack(list*);
void printList(list*);
void reverseList(list*);
void destroyList(list*);
void printReverseList(list*);

// void insert(???);
// void remove(???);
// void addLeft
// ??? find
// sort