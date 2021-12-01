#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"

list* createList()
{
	list* l = (list*)malloc(sizeof(list));
	l->size = 0;
	l->head = 0;
	l->tail = 0;
}
void destroyList(list* l)
{
	node* current = l->head;
	node* tmp;
	while (current != 0)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(l);
}
void pushBack(list* l, int _value)
{
	node* newElem = (node*)malloc(sizeof(node));
	newElem->value = _value;
	newElem->next = 0;

	if (l->tail != 0)
		l->tail->next = newElem;
	l->tail = newElem;

	if (l->head == 0)
		l->head = newElem;

	l->size++;
}
void printList(list* l)
{
	printf_s("Linked_List : \n");
	node* current = l->head;
	while (current != 0)
	{
		printf_s("%d ", current->value);
		current = current->next;
	}
	printf_s("\n");
}
void addRandom(list* l, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		pushBack(l, rand() % 10);
	}
}
void printReverseNodes(node* n)
{
	if (n == 0)
		return;
	printReverseNodes(n->next);
	printf_s("%d ", n->value);
}
void printReverseList(list* l)
{
	printf_s("printReverseList : \n");
	printReverseNodes(l->head);
	printf_s("\n");
}
void reverseList(list* l)
{
	node* saveTail = l->tail;
	l->tail = l->head;
	node* previous = 0, * current = l->head, * following = l->head;
	l->head = saveTail;
	while (current != 0)
	{
		following = following->next;
		current->next = previous;
		previous = current;
		current = following;
	}
}
int popBack(list* l)
{
	int result = 0;
	if (l->tail != 0)
	{
		result = l->tail->value;
		l->size--;
	}
	else
		printf_s("Empty list popBack error.\n");
	node* current = l->head;
	if (current != 0)
	{
		while (current->next != l->tail)
			current = current->next;
		free(current->next);
	}
	l->tail = current;
	if (l->tail != 0)
		l->tail->next = 0;
	return result;
}