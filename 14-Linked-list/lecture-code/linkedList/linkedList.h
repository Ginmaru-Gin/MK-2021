#pragma once

#include <stdio.h>

struct Node
{
	int value;
	struct Node* next;
};

typedef struct Node node;

struct LinkedList
{
	node* head;
	node* tail;
	size_t size;
};

typedef struct LinkedList linkedList;

linkedList* createList();
void pushBack(linkedList*, int);
void pushFront(linkedList*, int);
void addRandom(linkedList*, size_t);
int popBack(linkedList*);
int popFront(linkedList*);
int front(linkedList*);
void printList(linkedList*);
void reverseList(linkedList*);
void printReverseList(linkedList*);
int getMiddleElem(linkedList*);
void destroyList(linkedList*);

// need to implement
// void insert(linkedList* l, int newValue);
// void remove(linkedList* l, int removedValue);
// void removeAll(linkedList* l, int removedValue);
// node* find(linkedList* l, int findValue);