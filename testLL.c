#include "linkedList.h"

int main(){
	linkedList myList;
	node myNode;
	char *a, *b, *c, *d, *z;
	int size = 0;

	a = (char*)malloc(sizeof(char*));
	b = (char*)malloc(sizeof(char*));
	c = (char*)malloc(sizeof(char*));
	d = (char*)malloc(sizeof(char*));
	z = (char*)malloc(sizeof(char*));

	*a = 'A';
	*b = 'B';
	*c = 'C';
	*d = 'D';
	*z = 'Z';

	myList = makeLL();

	myNode = createNode(z);
	insert(myList, myNode);
	myNode = createNode(a);
	insert(myList, myNode);
	myNode = createNode(b);
	insert(myList, myNode);
	myNode = createNode(c);
	insert(myList, myNode);

	traverse(myList);

	deleteNode(myList);
	traverse(myList);

	eraseList(myList);
	traverse(myList);

	myNode = createNode(a);
	insert(myList, myNode);
	myNode = createNode(b);
	insert(myList, myNode);
	myNode = createNode(c);
	insert(myList, myNode);
	traverse(myList);

	return 0;
}