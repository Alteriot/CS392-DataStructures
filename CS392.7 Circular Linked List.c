
#include <stdio.h>
#include <stdlib.h>
#define item int
#define garb 333

typedef struct linked_list {
	int data;
	struct linked_list *link;
}node;

node* makeNode(int);
node* getCurrent(node *, int);
node* getPrevious(node *, int);
void insBeginCList(node **, node **, int);
void insAtCList(node *, int, int);
void appendCList(node **, int);
int delBeginCList(node **, node**);
int delAtCList(node *, int);
void deleteList(node **);
void display(node *);
int search(node *, int);
int length1(node *, node *);
int length2(node *);

node* makeNode(int data) {
	node *newNode;
	newNode = (node *)malloc(sizeof(node));
	newNode->link = newNode;
	newNode->data = data;
	return newNode;
}

node* getCurrent(node *head, int pos) {
	node *temp = head;
	int count = 1;
	do{						
		if(count == pos) return temp;
		temp = temp->link;
		count++;
	}while(temp != head);
	return NULL;
}

node* getPrevious(node *head, int pos) {
	node *temp = head;
	int count = 1;
	while(temp->link != head) {
		if(count == pos-1) return temp;
		temp = temp->link;
		count++;
	}
	return NULL;
}

//--------------------------------------------------------INSERTION FUNCTIONS---------------------------------------------------------------

void insBeginCList(node **head, node **rear, int data){
	node *newNode = makeNode(data);
	if(*head == NULL){
		newNode->link = newNode;
		*rear = newNode;
	}
	else{
		newNode->link = *head;
		(*rear)->link = newNode;
	}
	*head = newNode;
}		

void insAtCList(node *head, int pos, int data) {
	node *curr = getPrevious(head, pos);
	node *temp = makeNode(data);
	if(pos < 1 || curr == NULL) return;
	temp->link = curr->link;
	curr->link = temp;
}

void appendCList(node **rear, int data){
	node *temp = makeNode(data);
	if(*rear == NULL) temp->link = temp;
	else{
		temp->link = (*rear)->link;
		(*rear)->link = temp;
	}
	*rear = temp;
}

//--------------------------------------------------------DELETION FUNCTIONS---------------------------------------------------------------

int delBeginCList(node **head, node**rear){
	if(*rear == NULL) return 1;
	else{
		node *temp = (*rear)->link;
		(*rear)->link = ((*rear)->link)->link;
		*head = temp->link;
		free(temp);
		return 0;
	}
}

int delAtCList(node *head, int pos){
	node *p = getPrevious(head,pos);
	if(p->link == NULL) return 1;
	else{
		node *temp = p->link;
		p->link = temp->link;
		free(temp);
		return 0;
	}
}

void deleteList(node **head){
	node *temp = *head;
	do{
		temp = (temp)->link;
		free(temp);
	}while(temp != *head);
}
/*
*/

//--------------------------------------------------------DISPLAY FUNCTIONS----------------------------------------------------------------

void display(node *head) {
    int nodeno = 1;
	node *temp = head;
	do{
		printf("Node %d: %p\tNode->data: %d\tNode->link: %p\n",nodeno,temp,temp->data,temp->link);
		nodeno++;
		temp = temp->link;
	}while(temp != head);
}
/*
(1) While header is not NULL, or while the linked list is not end (when linked list ends then link will become NULL):
(2) Print the head->data and continue traversing from one node to another by head = head->link; and nodeno++; and keep on printing the elements.
*/

int search(node *head, item data) {
	node *temp = head;
	int count = 1;
	do{
		if(temp->data == data)
			return count;
		temp = temp->link;
		count++;
	}while(temp != NULL);
	return 0;
}

int length1(node *head, node *temp){
    if(temp->link==head) return 1;
    return 1+length1(head,temp->link);
}

//-----------------------------------------------------------MAIN FUNCTION------------------------------------------------------------------

int main() {
	node *head = NULL, *rear = NULL;
	int data, pos, x;
	while(1) {
		printf("===============================================================================\n");
		printf("MENU:\n");
		printf("  1.INSERT AT BEGINNING\n");
		printf("  2.INSERT IN MIDDLE\n");
		printf("  3.INSERT AT THE END (APPEND)\n");
		printf("  4.DELETE AT BEGINNING (DELETE HEADER)\n");
		printf("  5.DELETE IN MIDDLE\n");
		printf("  6.DELETE THE ENTIRE LIST (X)\n");
		printf("  7.LENGTH OF LINKED LIST\n");
		printf("  8.SEARCH A DATA\n");
		printf("  9.DISPLAY THE LIST\n");
		printf("  0.EXIT\n");
		printf("Enter your choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
		switch(user_ch) {
			case 1: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					insBeginCList(&head, &rear, data);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 2: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					printf("Enter the position at which you want to insert (can't be negative or 0): ");
					scanf("%d", &pos);
					if(pos > length1(head,head) || pos < 1){
						printf("Position invalid. Insertion unsuccessful!");
						printf("x");
                    }
					else insAtCList(head, pos, data);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 3: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					appendCList(&rear, data);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 4: printf("Data being deleted... \n");
					x = delBeginCList(&head,&rear);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 5: printf("Enter the position of the data to be removed: ");
					scanf("%d", &pos);
					if(pos > length1(head,head))
						printf("Position out of bound. Deletion unsuccessful!");
					else {
					printf("Data being deleted... \n");
					x = delAtCList(head,pos);
					if(x==1) printf("Deletion unsuccessful!\n");
					}
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 6: deleteList(&head); printf("Full list being deleted... \n");
			break;
			case 7: printf("Calculating length... \n");
					x = length1(head,head);
					printf("Length is: %d \n",x);
			break;
			case 8: printf("Enter the data to be searched in the List: ");
					scanf("%d", &data);
					pos = search(head, data);
					if(pos == 0) printf("Element not found in List.\n");
					else printf("Element found in List. Position: %d\n", pos);
			break;
			case 9: if(head == NULL) printf("The List is Empty.\n");
					else {
						printf("The Linked List:\n\n");
						display(head);
					}
					printf("\n");
			break;
			case 0: printf("Exiting Program......\n\n"); return 0;
			break;
			default: printf("Wrong Input! Try Again.\n\n");
			break;
		}
	}
	return 0;
}
