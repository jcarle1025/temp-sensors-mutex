#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct node{
	void * item;
	struct node *next;
}node_t;

typedef struct linkedList{
	node_t *headNode;
	node_t *lastNode;
}linkedList_t;

typedef linkedList_t * linkedList;
typedef node_t * node;

linkedList makeLL();
node createNode(void *data);
void insert(linkedList myLL, node newNode);
void deleteNode(linkedList myLL);
void traverse(linkedList myLL);
void eraseList(linkedList myLL); //traverses and delete, free all nodes
int getSize(linkedList myLL);


