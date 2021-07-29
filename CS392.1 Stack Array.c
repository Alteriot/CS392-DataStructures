
#include<stdio.h>
#include<stdlib.h>
#define item int
#define garb 333

typedef struct adt{
	item *arr;
	int size, TOS;
}stack;

void init(stack*,int);
int isEmpty(stack*);
int isFull(stack*);
void push(stack*,item);
item pop(stack*);
item peek(stack*);

void init(stack *s, int n){
	s->TOS = -1;
	s->size = n;
	s->arr = (item *)malloc(sizeof(item)*(s->size));
}

int isEmpty(stack *s){
	return (s->TOS == -1);
}

int isFull(stack *s){
	return (s->TOS == (s->size)-1);
}

void push(stack *s, item data){
	if(isFull(s)) {
		printf("Stack Overflow!!!");
	return;
	}
	(s->TOS)++;
	s->arr[s->TOS] = data;
}

item pop(stack *s){
	if(isEmpty(s)) return garb;
	return s->arr[(s->TOS)--];
}

item peek(stack *s){
	if(isEmpty(s)) return garb;
	return s->arr[(s->TOS)];
}

int main(){
	stack s;
	int n;
	printf("\nEnter the size of the Stack: ");
	scanf("%d",&n);
	printf("\nInitializing the Stack...");
	init(&s,n);
	printf("\nOperating on the stack....");
	while(1){
		printf("\nMenu: ");
		printf("\n1: PUSH");
		printf("\n2: POP");
		printf("\n3: PEEK");
		printf("\n4: EXIT");
		printf("\nEnter your choice: ");
		int ch;
		item data;
		scanf("%d",&ch);
		switch(ch){
			case 1: printf("\nEnter data to be pushed inside the Stack: ");
					scanf("%d",&data);
					push(&s,data);
					break;
			case 2: data = pop(&s);
					if(data == garb) printf("\nStack Underflow!!");
					else printf("\nPopped element: %d",data);
					break;
			case 3: data = peek(&s);
					if(data == garb) printf("\nStack Empty!!!");
					else printf("Last inserted data: %d",data);
					break;
			case 4: return 0;
			default: printf("Wrong choice!");
		}
	}
	return 0;
}
