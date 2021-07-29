
#include <stdio.h>
#include <stdlib.h>
#define item int
#define garb 333

typedef struct linked_list {
	item data;
	struct linked_list *prevlink;
	struct linked_list *nextlink;
}dllnode;

dllnode* makeNode(int);
dllnode* getCurrent(dllnode *, int);
void insBegin(dllnode **, dllnode **, item);
void insAfter(dllnode *, int, item);
void append(dllnode **, dllnode **, item);
int delBegin(dllnode **, dllnode **);
int delAt(dllnode *, dllnode *, int);
void display(dllnode *, dllnode *);
int search(dllnode *, item);
int length(dllnode *);

//-----------------------------------------------------------------------------------------------------------------------------------------

dllnode* makeNode(int data) {
	dllnode *newNode;
	newNode = (dllnode *)malloc(sizeof(dllnode));
	newNode->prevlink = NULL;
	newNode->nextlink = NULL;
	newNode->data = data;
	return newNode;
}

dllnode* getCurrent(dllnode *head, int pos) {
	dllnode *temp = head;
	int count = 1;
	while(temp != NULL) {
		if(count == pos) return temp;
		temp = temp->nextlink;
		count++;
	}
	return NULL;
}

void insBegin(dllnode **head, dllnode **tail, item data) {
	dllnode *newNode = makeNode(data);
	newNode->prevlink = NULL;
	if(*head == NULL){
		*head = *tail = newNode;
		newNode->nextlink = NULL;
	}
	else{
		newNode->nextlink = *head;
		(*head)->prevlink = newNode;
	}
	*head = newNode;
}

void insAfter(dllnode *head, int pos, item data) {
	dllnode *curr = getCurrent(head, pos);
	if(pos < 1 || curr == NULL) return;
	dllnode *temp = makeNode(data);
	temp->prevlink = curr;
	temp->nextlink = curr->nextlink;
	(temp->prevlink)->nextlink = temp;
	(temp->nextlink)->prevlink = temp;
}

void append(dllnode **head, dllnode **tail, item data) {
	if(*head == NULL) {
		insBegin(head, tail, data);
		return;
	}
	dllnode *newNode = makeNode(data);
	newNode->nextlink = NULL;
	newNode->prevlink = *tail;
	(*tail)->nextlink = newNode;
	*tail = newNode;
}

//--------------------------------------------------------DELETION FUNCTIONS---------------------------------------------------------------

int delBegin(dllnode **head, dllnode **tail){
	if(*head == NULL) return 0;
	else{
		dllnode *temp = *head;
		if(*head == *tail) *head = *tail = NULL;
		else{
			*head = (*head)->nextlink;
			(*head)->prevlink = NULL;
		}
	return temp->data;
	free(temp);
    }
}

int delAt(dllnode **head, dllnode **tail, int pos){
	dllnode *temp = getCurrent(*head, pos);
	if(temp == NULL) return 1;
	else if(temp->prevlink == NULL) delBegin(head,tail);
	else if(temp->nextlink == NULL){
		(temp->prevlink)->nextlink = NULL;
		*tail = temp->prevlink;
		free(temp);
		return 0;
	}
	else{
		(temp->prevlink)->nextlink = temp->nextlink;
		(temp->nextlink)->prevlink = temp->prevlink;
		free(temp);
		return 0;
	}
}
/*
void deleteList(node **head){
	node *temp;
	while(*head != NULL){
		temp = *head;
		*head = (*head)->link;
		free(temp);
	}
}
*/

//--------------------------------------------------------DISPLAY FUNCTIONS----------------------------------------------------------------

void display(dllnode *head, dllnode *tail) {
    int nodeno = 1;
	if(head == NULL) return;
	else{
		dllnode *temp = head;
		while(temp != NULL) {
			printf("N%d: %p\tData: %d\tPrevlink: %p\tNextlink: %p\n",nodeno, temp, temp->data, temp->prevlink, temp->nextlink);
			nodeno++;
			temp = temp->nextlink;
		}
	}
}

int search(dllnode *head, item data) {
	dllnode *temp = head;
	int count = 1;
	while(temp != NULL) {
		if(temp->data == data)
			return count;
		temp = temp->nextlink;
		count++;
	}
	return 0;
}

int length(dllnode *head){
    if (head == NULL)
        return 0;
    return 1 + length(head->nextlink);
}

//-----------------------------------------------------------MAIN FUNCTION-----------------------------------------------------------------

int main() {
	dllnode *head = NULL, *tail = NULL;
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
		printf("head: %p, tail: %p",head,tail);
		printf("\nEnter your choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		switch(user_ch) {
			case 1: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					insBegin(&head,&tail,data);
			break;
			case 2: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					printf("Enter the position after which you want to insert (can't be negative or 0): ");
					scanf("%d", &pos);
					if(pos > length(head) || pos < 1)
						printf("Position invalid. Insertion unsuccessful!");
					else if(pos == length(head)) append(&head,&tail,data);
					else insAfter(head, pos, data);
			break;
			case 3: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					append(&head,&tail,data);
			break;
			case 4: printf("Data being deleted... \n");
					x = delBegin(&head,&tail);
			break;
			case 5: printf("Enter the position of the data to be removed: ");
					scanf("%d", &pos);
					if(pos > length(head))
						printf("Position out of bound. Deletion unsuccessful!");
					else {
					printf("Data being deleted... \n");
					x = delAt(&head,&tail,pos);
					if(x==1) printf("Deletion unsuccessful!\n");
					}
			break;
			case 6: //deleteList(&head,&tail);
			break;
			case 7: printf("Calculating length... \n");
					x = length(head);
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
						display(head,tail);
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

