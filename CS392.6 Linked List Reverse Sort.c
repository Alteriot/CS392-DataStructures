#include <stdio.h>
#include <stdlib.h>
#define item int

typedef struct linked_list {
	item data;
	struct linked_list *link;
}node;

node* getNode(item);
node* getCurrent(node *, int);
node* getPrevious(node *, int);
void show(node *);
void insBegin(node **, item);
void insAfter(node *, int, item);
void append(node **, item);
int search(node *, item);
void reverse(node **);
void insertionSort(node **);
void bubbleSort(node *);
void swap(node *, node *);

node* makeNode(item data) {
	node *newNode;
	newNode = (node *)malloc(sizeof(node));
	newNode->link = NULL;
	newNode->data = data;
	return newNode;
}

node* getCurrent(node *head, int pos) {
	node *temp = head;
	int count = 1;
	while(temp != NULL) {
		if(count == pos)
			return temp;
		temp = temp->link;
		count++;
	}
	return NULL;
}

node* getPrevious(node *head, int pos) {
	if(head == NULL) return NULL;
	node *temp = head;
	int count = 1;
	while(temp->link != NULL) {
		if(count == pos-1)
			return temp;
		temp = temp->link;
		count++;
	}
	return NULL;
}

void show(node *head) {
	while(head != NULL) {
		printf("%d ", head->data);
		head = head->link;
	}
}

void insAfter(node *head, int pos, item data) {
	node *curr = getCurrent(head, pos);
	if(pos < 1 || curr == NULL) return;
	node *temp = makeNode(data);
	temp->link = curr->link;
	curr->link = temp;	
}

void insBegin(node **head, item data) {
	node *temp = makeNode(data);
	temp->link = *head;
	*head = temp;
}

void append(node **head, item data) {
	if(*head == NULL) {
		insBegin(head, data);
		return;
		}
	node *newNode = makeNode(data), *temp = *head;
	while(temp->link != NULL) {
		temp = temp->link;
	}
	temp->link = newNode;
}

int length(node *head){
    if (head == NULL)
        return 0;
    return 1 + length(head->link);
}

//-----------------------------------------------------------REVERSE AND SORT--------------------------------------------------------------
void reverse(node **head){
	node *prev = NULL, *next, *curr = *head;
	while(curr != NULL){
		next = curr->link;
		curr->link = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

void insertionSort(node **head){
	node *outPrev, *outCurr, *inPrev, *inCurr;
	for(outPrev = *head, outCurr = (*head)->link; outCurr != NULL;  ) //No increment done in here; as increment is done inside.
	{
		for(inCurr = *head, inPrev = NULL; outCurr->data > inCurr->data && inCurr != outCurr; inPrev = inCurr, inCurr = inCurr->link);
		if(inCurr == outCurr){				//Entire list searched, no suitable position found.
			outPrev = outPrev->link;
			outCurr = outCurr->link;		//The increment I for 'for loop'.
			}
		else {
			if(inPrev!=NULL){
				outPrev->link = outCurr->link;
				outCurr->link = inCurr;
				inPrev->link = outCurr;
				outCurr = outPrev->link;	//The increment II for 'for loop'.
				}
			else{
				outPrev->link = outCurr->link;
				outCurr->link = inCurr;
				*head = outCurr;
				outCurr = outPrev->link;	//The increment II for 'for loop'.
			}
		}
	}
}

void bubbleSort(node *head){
    int swapped, i;
    node *ptr1;
    node *lptr = NULL;
    if (head == NULL)
        return;
    do{
        swapped = 0;
        ptr1 = head;
        while (ptr1->link != lptr){
            if (ptr1->data > (ptr1->link)->data){ 
                swap(ptr1, ptr1->link);
                swapped = 1;
            }
            ptr1 = ptr1->link;
        }
        lptr = ptr1;
    }
    while(swapped);
}

void swap(node *a, node *b){
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
	
//-----------------------------------------------------------MAIN FUNCTION------------------------------------------------------------------
int main() {
	node *head = NULL;
	int data, pos;
	while(1) {
		printf("===============================================================================\n");
		printf("MENU:\n");
		printf("  1.ADD AT THE BEGINNING\n");
		printf("  2.INSERT IN MIDDLE\n");
		printf("  3.APPEND AT THE END\n");
		printf("  4.DISPLAY THE LIST\n");
		printf("  5.REVERSE\n");
		printf("  6.INSERTION SORT(ASCENDING)\n");
		printf("  7.BUBBLE SORT (ASCENDING)\n");
		printf("  0.EXIT\n");
		printf("Enter your choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		switch(user_ch) {
			case 1: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					insBegin(&head, data);
			break;
			case 2: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					printf("Enter the position after which you want to insert (can't be negative or 0): ");
					scanf("%d", &pos);
					if(pos > length(head) || pos < 1)
						printf("Position invalid. Insertion unsuccessful!");
					else insAfter(head, pos, data);
			break;
			case 3: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					append(&head, data);
			break;
			case 4: if(head == NULL) printf("The List is Empty.\n");
					else {
						printf("The Linked List:\n\n");
						show(head);
					}
					printf("\n");
			break;
			case 5: reverse(&head); show(head); printf("\n");
			break;
			case 6: insertionSort(&head); show(head); printf("\n");
			break;
			case 7: bubbleSort(head); show(head); printf("\n");
			break;
			case 0: printf("Exiting Program......\n\n"); return 0;
			break;
			default: printf("Wrong Input! Try Again.\n\n");
			break;
		}
	}
	return 0;
}