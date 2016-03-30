#include "linkedList.h"

linkedList makeLL(){
	linkedList myLL;
	myLL = (linkedList)malloc(sizeof(linkedList_t));
	myLL->headNode = NULL;
	myLL->lastNode = NULL;

	return myLL;
}

node createNode(void *data){
	node myNode = malloc(sizeof(node));
	myNode->next = NULL;
	myNode->item = data;
	return myNode;
}

void insert(linkedList myLL, node newNode){
	if(myLL->headNode == NULL){
		printf("inserting %d... \n", *((int*)newNode->item));
		myLL->headNode = newNode;
		myLL->lastNode = newNode;
	}

	else{
		printf("inserting %d... \n", *((int*)newNode->item));
		myLL->lastNode->next = newNode;
		myLL->lastNode = newNode;
	}
}

void deleteNode(linkedList myLL){//deltes last node
	node temp = myLL->headNode;
	node temp2;
	if (temp->next == NULL){
		free(myLL);
		linkedList another = makeLL();
	}

	while(temp->next->next != NULL){
		temp = temp->next;
	}

	temp2 = temp->next;
	temp->next = NULL;
	free(temp2);
	myLL->lastNode = temp;
}

void traverse(linkedList myLL){
	node temp;
	temp = myLL->headNode;

	if(temp == NULL)
		printf("EMPTY LIST\n\n");

	else{
		printf("Printing List...\n{");
		while(temp->next != NULL){
			printf("%d, ", *((int*)temp->item));
			temp = temp->next;
		}

		printf("%d}\n", *((int*)temp->item));
	}
}

void average(linkedList myLL){
	node temp;
	double sum=0;
	double avg;
	temp = myLL->headNode;
	
	while(temp->next != NULL){
		sum = sum+*((int*)(temp->item));
		temp = temp->next;
	}
	
	sum = sum+*((int*)(temp->item));
	avg = sum/getSize(myLL);
	
	printf("Average Temp = %f\n\n", avg);
}

void eraseList(linkedList myLL){
	free(myLL);
	myLL = makeLL();
}

int getSize(linkedList myLL){
	int size = 0;
	node temp = myLL->headNode;

	if(temp == NULL)
		return size;

	while(temp->next != NULL){
		size ++;
		temp = temp->next;
	}
	return size+1;
}
