#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedList.h"

int main()
{
	srand((unsigned int)time(0));

	linkedList* l1 = createList();
	popBack(l1);
	addRandom(l1, 10);
	printList(l1);
	printReverseList(l1);
	reverseList(l1);
	printf_s("After reverse :\b");
	printList(l1);
	printReverseList(l1);

	popBack(l1);
	popBack(l1);
	printf_s("After two popBack size = %lu\n", l1->size);
	printList(l1);
	destroyList(l1);

	l1 = createList();
	addRandom(l1, 5);
	printList(l1);
	printf_s("Middle value = %d\n", getMiddleElem(l1));
	destroyList(l1);

	return 0;
}