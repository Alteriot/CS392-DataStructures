
#include<stdio.h>
#include<stdlib.h>
#define item int
#define garb 33399

typedef struct queueNode {
	item data;
	struct queueNode *link;
}qnode;

qnode* makeNode();
void insertBegin(qnode **, item);
void append_or_enq(qnode **, item);
int delBeginWithReturn_or_deq(qnode **);
item peek(qnode *);

qnode* makeNode() {
	qnode *newNode;
	newNode = (qnode *)malloc(sizeof(qnode));
	newNode->link = NULL;
	return newNode;
}

void insertBegin(qnode **head, item data) {
	qnode *newNode = makeNode();
	newNode->link = *head;
	newNode->data = data;
	*head = newNode;
}

void append_or_enq(qnode **head, item data) {
	if(*head == NULL) {
		insertBegin(head, data);
		return;
		}
	qnode *newNode = makeNode(), *temp = *head;
	newNode->data = data;
	while(temp->link != NULL) {
		temp = temp->link;
	}
	temp->link = newNode;
}

item delBeginWithReturn_or_deq(qnode **head){
	if(*head == NULL) return garb;
	else{
		item returnval;
		qnode *temp = *head;
		returnval = (*head)->data;
		*head = (*head)->link;
		free(temp);
		return returnval;
	}
}

item peek(qnode *head){
	if (head == NULL)  return garb;
	return head->data;
}

//-------------------------------------------------------------MAIN FUNCTION-----------------------------------------------------------------
int main(){
	qnode *q = NULL;
	printf("\nOperating on the queue....");
	while(1){
        printf("\n#################################################################");
		printf("\nMenu: ");
		printf("\n1 -> Enqueue");
		printf("\n2 -> Dequeue");
		printf("\n3 -> Peek");
		printf("\n4 -> EXIT");
		printf("\nEnter your choice: ");
		int ch;
		item data;
		scanf("%d",&ch);
		switch(ch){
			case 1: printf("\nEnter data to be enqueued: ");
					scanf("%d",&data);
					append_or_enq(&q,data);
					break;
			case 2: data = delBeginWithReturn_or_deq(&q);
					if(data == garb) printf("\nQueue Underflow!!");
					else printf("\nDequeued element: %d",data);
					break;
			case 3: data = peek(q);
					if(data == garb) printf("\nQueue Empty!!!");
					else printf("\nLast inserted data: %d",data);
					break;
			case 4: return 0;
			default: printf("\nWrong choice!");
		}
	}
	return 0;
}
