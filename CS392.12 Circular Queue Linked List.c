
#include <stdio.h>
#include <stdlib.h>
#define item int
#define garb 333

typedef struct linked_list {
	int data;
	struct linked_list *link;
}cqnode;

cqnode* makeNode(int);
void appendCList(cqnode **, int);
int delBeginCList(cqnode **, cqnode**);
int length2(cqnode *);

cqnode* makeNode(int data) {
	cqnode *newNode;
	newNode = (cqnode *)malloc(sizeof(cqnode));
	newNode->link = newNode;
	newNode->data = data;
	return newNode;
}

//--------------------------------------------------------INSERTION FUNCTIONS---------------------------------------------------------------

void appendCList(cqnode **rear, int data){
	cqnode *temp = makeNode(data);
	if(*rear == NULL) temp->link = temp;
	else{
		temp->link = (*rear)->link;
		(*rear)->link = temp;
	}
	*rear = temp;
}

//--------------------------------------------------------DELETION FUNCTIONS---------------------------------------------------------------

int delBeginCList(cqnode **head, cqnode **rear){
	if(*rear == NULL) return 1;
	else{
		cqnode *temp = (*rear)->link;
		(*rear)->link = ((*rear)->link)->link;
		*head = temp->link;
		free(temp);
		return 0;
	}
}

//--------------------------------------------------------DISPLAY FUNCTIONS----------------------------------------------------------------

int peekCQ(cqnode *head){
	if(head==NULL) return 0;
	return head->data;
}

//-----------------------------------------------------------MAIN FUNCTION------------------------------------------------------------------

int main() {
	cqnode *head = NULL, *rear = NULL;
	int data, pos, x;
	while(1) {
		printf("===============================================================================\n");
		printf("MENU:\n");
		printf("  1.ENQUEUE (APPEND)\n");
		printf("  2.DEQUEUE (DELETE HEADER)\n");
		printf("  3.PEEK\n");
		printf("  0.EXIT\n");
		printf("Enter your choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		printf("\nHead: %p, Tail: %p\n",head,rear);
		switch(user_ch) {
			case 1: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					appendCList(&rear, data);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 2: printf("Data being deleted... \n");
					x = delBeginCList(&head,&rear);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 3: printf("Peeked value: \n");
					peekCQ(head);
			break;
			case 0: printf("Exiting Program......\n\n"); return 0;
			break;
			default: printf("Wrong Input! Try Again.\n\n");
			break;
		}
	}
	return 0;
}
