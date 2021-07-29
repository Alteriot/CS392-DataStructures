
#include<stdio.h>
#include<stdlib.h>
#define item int
#define garb 33399

typedef struct stackNode {
	item data;
	struct stackNode *link;
}snode;

snode* makeNode();
void insertBegin(snode **, item);
int delBeginWithReturn_or_Pop(snode **);
item peek(snode *);

snode* makeNode() {
	snode *newNode;
	newNode = (snode *)malloc(sizeof(snode));
	newNode->link = NULL;
	return newNode;
}

void insertBegin_or_Push(snode **head, item data) {
	snode *newNode = makeNode();
	newNode->link = *head;
	newNode->data = data;
	*head = newNode;
}

item delBeginWithReturn_or_Pop(snode **head){
	if(*head == NULL) return garb;
	else{
		item returnval;
		snode *temp = *head;
		returnval = (*head)->data;
		*head = (*head)->link;
		free(temp);
		return returnval;
	}
}

item peek(snode *head){
	if (head == NULL)  return garb;
	return head->data;
}

//-------------------------------------------------------------MAIN FUNCTION-----------------------------------------------------------------
int main(){
	snode *s = NULL;
	printf("\nOperating on the stack....");
	while(1){
		printf("\n#################################################################");
		printf("\nMenu: ");
		printf("\n1 -> Push");
		printf("\n2 -> Pop");
		printf("\n3 -> Peek");
		printf("\n4 -> EXIT");
		printf("\nEnter your choice: ");
		int ch;
		item data;
		scanf("%d",&ch);
		switch(ch){
			case 1: printf("\nEnter data to be pushed inside the Stack: ");
					scanf("%d",&data);
					insertBegin_or_Push(&s,data);
					break;
			case 2: data = delBeginWithReturn_or_Pop(&s);
					if(data == garb) printf("\nStack Underflow!!");
					else printf("\nPopped element: %d",data);
					break;
			case 3: data = peek(s);
					if(data == garb) printf("\nStack Empty!!!");
					else printf("Last inserted data: %d",data);
					break;
			case 4: return 0;
			default: printf("Wrong choice!");
		}
	}
	return 0;
}
