
#include <stdio.h>
#include <stdlib.h>
#define item int
#define garb 333

typedef struct linked_list {
	item data;
	struct linked_list *link;
}node;

node* makeNode();
node* getCurrent(node *, int);
node* getPrevious(node *, int);
void insBegin(node **, item);
void insAfter(node *, int, item);
void insAt(node *, int, item);
void append(node **, item);
int delBegin(node **);
void display(node *);
int search(node *, item);
int length(node *);

node* makeNode() {
	node *newNode;
	newNode = (node *)malloc(sizeof(node));
	newNode->link = NULL;
	return newNode;
}

node* getCurrent(node *head, int pos) {
	node *temp = head;
	int count = 1;
	while(temp != NULL) {							//while(count<pos)??
		if(count == pos) return temp;
		temp = temp->link;
		count++;
	}
	return NULL;
}

node* getPrevious(node *head, int pos) {
	node *temp = head;
	int count = 1;
	while(temp->link != NULL) {
		if(count == pos-1) return temp;
		temp = temp->link;
		count++;
	}
	return NULL;
}

//--------------------------------------------------------INSERTION FUNCTIONS---------------------------------------------------------------
void insBegin(node **head, item data) {
	node *newNode = makeNode();			//makeNode() makes a node and returns its address; it's stored at newNode now.
	newNode->link = *head;				//The old header's address is stored at the link part of new node.
	newNode->data = data;
	*head = newNode;					//newNode is the new header of the linked list now; thus node successfully added at the beginning.
}

void insAfter(node *head, int pos, item data) {
	node *curr = getCurrent(head, pos);
	//if(pos < 1 || curr == NULL) return;	
	node *temp = makeNode();
	temp->data = data; 
	temp->link = curr->link;
	curr->link = temp;	
}

void insAt(node *head, int pos, item data) {
	node *curr = getPrevious(head, pos);
	//if(pos < 1 || curr == NULL) return;	
	node *temp = makeNode();
	temp->data = data; 
	temp->link = curr->link;
	curr->link = temp;	
}

void append(node **head, item data) {
	node *newNode = makeNode(), *temp = *head;
	newNode->data = data;
	while(temp->link != NULL) {
		temp = temp->link;
	}
	temp->link = newNode;
}

//--------------------------------------------------------DELETION FUNCTIONS---------------------------------------------------------------

int delBegin(node **head){
	if(*head == NULL) return 0;
	else{
		node *temp = *head;
		*head = (*head)->link;
		item deleted = temp->data;
		free(temp);
		return deleted;
	}
}

int delAt(node *head, int pos){
	node *p = getPrevious(head,pos);
	if(p->link == NULL) return 0;
	else{
		node *temp = p->link;
		p->link = temp->link;
		item deleted = temp->data;
		free(temp);
		return deleted;
	}
}

void deleteList(node **head){
	node *temp;
	while(*head != NULL){
		temp = *head;
		*head = (*head)->link;
		free(temp);
	}
}
/*
*/

//--------------------------------------------------------DISPLAY FUNCTIONS----------------------------------------------------------------

void display(node *head) {
    int nodeno = 1;
	while(head != NULL) {
		printf("Node %d: %p\tNode->data: %d\tNode->link: %p\n",nodeno,head,head->data,head->link);
		nodeno++;
		head = head->link;
	}
}

int search(node *head, item data) {
	node *temp = head;
	int count = 1;
	while(temp != NULL) {
		if(temp->data == data)
			return count;
		temp = temp->link;
		count++;
	}
	return 0;
}

int length(node *head){
    if (head == NULL)
        return 0;
    return 1 + length(head->link);
}

//-----------------------------------------------------------MAIN FUNCTION------------------------------------------------------------------

int main() {
	node *head = NULL;
	int data, pos, x;
	while(1) {
		printf("===============================================================================\n");
		printf("MENU:\n");
		printf("  1.INSERT DATA\n");
		printf("  2.DELETE DATA\n");
		printf("  3.DELETE FULL LIST\n");
		printf("  4.LENGTH OF LINKED LIST\n");
		printf("  5.SEARCH A DATA\n");
		printf("  6.DISPLAY THE LIST\n");
		printf("  0.EXIT\n");
		printf("Enter your choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		switch(user_ch) {
			case 1: while(1){
						printf("Enter the position where you want to insert (can't be negative, 0 to exit): ");
						scanf("%d", &pos);
						if(pos==0) break;
						printf("Enter the data for the Node: ");
						scanf("%d", &data);
						if(pos > length(head)+1 || pos < 1) printf("Position invalid. Insertion unsuccessful!");
						else if(pos == 1) insBegin(&head, data);
						else if(pos == length(head)+1 && pos != 1) append(&head, data);
						else insAt(head, pos, data);
			}
			break;
			case 2: printf("Enter the position of the data to be removed: ");
					scanf("%d", &pos);
					printf("Data being deleted... \n");
					if(pos > length(head) || pos < 1){
						printf("Position invalid.");
					}
					else if(pos == 1){
						x = delBegin(&head);
						if(x==0) printf("Deletion unsuccessful!\n");
						else printf("Item deleted: %d",x);
					}
					else{
						x = delAt(head,pos);
						if(x==0) printf("Deletion unsuccessful!\n");
						else printf("Item deleted: %d",x);
					}
			break;
			case 3: deleteList(&head); printf("Full list being deleted... \n");
			break;
			case 4: printf("Calculating length... \n");
					x = length(head);
					printf("Length is: %d \n",x);
			break;
			case 5: printf("Enter the data to be searched in the List: ");
					scanf("%d", &data);
					pos = search(head, data);
					if(pos == 0) printf("Element not found in List.\n");
					else printf("Element found in List. Position: %d\n", pos);
			break;
			case 6: if(head == NULL) printf("The List is Empty.\n");
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
