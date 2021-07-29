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
	
int isEmpty(stack *s){
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

int pred(char ch){
	switch (ch)
	{
	case '(': return 0;
	case '+':
	case '-': return 1;
 	case '*':
	case '/': return 2;
	case '^': return 3;
	}
}
/*
In Infix->Postfix, this is the weightage or importance of operators. Higher number indicating more importance.
*/

int convert(char *arr){
	stack s;
	char z,arr2[20];
	int i,j;
	init(&s,strlen(arr));
/*
First we need to initialize the array, so that we can use stack functions like pop, push on the infix expressions. Applying characteristics of Stack datatype on infix->postfix expressions makes it easier to compute.
*/
	for(i=0,j=0;arr[i]!='\0';i++){
		if((arr[i]>='a' && arr[i]<='z') || (arr[i]>='A' && arr[i]<='Z') || (arr[i]>='0' && arr[i]<='9')){
			arr2[j++]=arr[i];
		}
/*
Here, arr[2] is storing the converted expression (or string). So, any operand will be copied from arr (infix) to arr2 (postfix). Here, the statement arr2[j++]=arr[i]; is same as: arr2[j]=arr[i]; j++; and arr2[++j]=arr[i]; is same as: j++; arr2[j]=arr[i]; statement.
We start with j=0 so j needs to be incremented to point to the next array location after copying the operand from infix to postfix.
*/
		else{
			switch(arr[i]){
				case '(': push(&s,arr[i]); break;
				case ')': do{
								z=pop(&s);
								if(z!='(') arr2[j++]=z;
							}
							while(z!='('); break;
				default: while(!isEmpty(&s) && pred(peek(&s))>=pred(arr[i])){
							arr2[j++]=pop(&s);
							}
				push(&s,arr[i]);
			}
		}
/*
If the array element is NOT an operand, rather, an operator, then some other stuff needs to be done:
[Consider: a+b*(c-d/e)+f, whose postfix: abcde/-*+f+]
(1) IF the operator is not ( or ) then, provided the stack isn't empty, calculate the precedence of the operator.
The operand, then will only be moved from stack to arr2[j] if the precedence of the TOS element is greater than the precedence of the infix element. Otherwise, it will be pushed into the stack.
(2) IF the operator is ( then push the ( inside stack.
(3) Continue normally after (, as in the default case.
(3) IF the operator is ) then pop the top from stack. If the popped element is not (, then keep popping & adding the popped elements in arr2.
(4) IF the popped element is ( then break from loop. Thus all elements from "(" to ")" has been added to arr2.
[In the example, first a -> arr2, then + -> stack, then b -> arr2. Then *. Pred(+)<Pred(*), so * -> stack.
Then ( so control enters case 1: ( -> stack. Then control goes back to "default case", c -> arr2, - -> stack [as Pred(()<Pred(-)], d -> arr2.
/ -> stack [as Pred(()<Pred(/)], e -> arr2. Then ). Now control goes to case 2; and all the stack elements (+,*,-,/) are popped to arr2[j] and j++ is done after every element, while (the popped element is not equal to '('. If it is, then popping is halted).
When popping a stack it follows LIFO, so last entered element will come first, so we will get output as /-*+ like that.
Then we have + -> stack, f -> arr2 and finally + -> arr2 at the end (see below).]
*/
	}
	while(!isEmpty(&s)){
		arr2[j++]=pop(&s);
		arr2[j]='\0';
	}
		for(i=0;i<strlen(arr2);i++) printf("%c",arr2[i]);
}
/*
The last + sign was moved from stack to arr[2] by arr2[j++]=pop(&s); and then arr2[j]='\0'; or a null character was added. Then the entire string was printed.
*/

int main(){
	char exp[30];
	printf("Infix Exp: ");
	fgets(exp,sizeof(exp),stdin);
	printf("\nConverted Postfix Exp: ");
	convert(exp);
	printf("\n");
		getch();
	return 0;
}
/*
The best way to take a string input is fgets(string_name,sizeof(string_name),stdin); because:
(1) In case of gets(): If array size is declared 5 and we put the name "Hello", then all 5 spaces will be utilized: NO NULL CHARACTERS!!
Then if we use puts(), puts() prints till '\0' is encountered, but there's no NULL here, so it will go on an infinite loop. 
(2) In case of scanf("%c",&arr[i]): An enter is necessary after every input.
*/
