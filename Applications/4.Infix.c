#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define item char
typedef struct Stack
{
	int TOS, size;
	char *arr;
}stack;

void init(stack *s, int n){
	s->TOS = -1;
	s->size = n;
	s->arr = (item *)malloc(sizeof(item)*(s->size));
}
	
int isEmpty(stack *s){												//PROGRAM UNDER CONSTRUCTION
	return (s->TOS == -1);
}

int isFull(stack *s){
	return (s->TOS == (s->size)-1);
}

item peek(stack *s){
	if(isEmpty(s)) return 0;
	return s->arr[(s->TOS)];
}

item pop(stack *s){
	if(isEmpty(s)) return 0;
	return s->arr[(s->TOS)--];
}

void push(stack *s, item data){
	if(isFull(s)) {
		printf("Stack Overflow!!!");
	return;
	}
	(s->TOS)++;
	s->arr[s->TOS] = data;
}
//-------------------------------------------------------------------------------------------------------------------------------------


int convert(char *arr){
	stack s;
	int i,j;
	init(&s,strlen(arr));

	for(i=0,j=0;arr[i]!='\0';i++){
		if((arr[i]>='a' && arr[i]<='z') || (arr[i]>='A' && arr[i]<='Z') || (arr[i]>='0' && arr[i]<='9')){
			push(&s,arr[i]-'0');
		}

		else{
			char op1 = pop(&s); char op2 = pop(&s);
			switch(arr[i]){
				case '+': push(&s,op2+op1); break;
				case '-': push(&s,op2-op1); break;
				case '*': push(&s,op2*op1); break;
				case '/': push(&s,op2/op1); break;
				case '^': push(&s,op2^op1); break;
			}
			//return pop(&s);
			printf("%c",pop(&s));
			}
		}
	}

int main(){
	char exp[30];
	printf("Postix Exp: ");
	fgets(exp,sizeof(exp),stdin);
	printf("\nConverted Infix Exp: ");
	convert(exp);
	printf("\n");
		getch();
	return 0;
}

