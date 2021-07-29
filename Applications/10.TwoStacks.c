#include<stdio.h>
#include<stdlib.h>

int pushone(int *arr, int data, int tos1){
    tos1++;
	arr[tos1] = data;
	return tos1;
}

int pushtwo(int *arr, int data, int tos2){
    tos2--;
	arr[tos2] = data;
	return tos2;
}

int popone(int *arr, int tos1){
    printf("Popped element: %d",arr[tos1]);
    tos1--;
	return tos1;
}

int poptwo(int *arr, int tos2){
	printf("Popped element: %d",arr[tos2]);
    tos2++;
	return tos2;
}

int peekone(int *arr, int tos1){
	return arr[tos1];
}

int peektwo(int *arr, int tos2){
	return arr[tos2];
}

int main(){
    int size, size1;
	printf("Combined size of stack 1 and stack 2: ");
	scanf("%d",&size);
	int tos1=-1, tos2=size;
	int *arr = (int *)malloc(size*sizeof(int));
	printf("Number of elements in stack 1: ");
	scanf("%d",&size1);
	printf("Then number of elements in stack 2 will be: %d",size-size1);
	while(1){
		printf("\nMENU: ");
		printf("\n1 PUSH IN STACK 1");
		printf("\n2 PUSH IN STACK 2");
		printf("\n3 POP STACK 1");
		printf("\n4 POP STACK 2");
		printf("\n5 PEEK STACK 1");
		printf("\n6 PEEK STACK 2");
		printf("\n0 EXIT");
		printf("\nEnter your choice: ");
		int ch;
		int data;
		scanf("%d",&ch);
		printf("TOS1: %d, TOS2: %d",tos1,tos2);
		switch(ch){
			case 1: printf("\nEnter data to be pushed inside the Stack 1: ");
					scanf("%d",&data);
					if(tos1==size1-1) printf("Stack overflow!");
					else tos1 = pushone(arr,data,tos1);
					break;
			case 2: printf("\nEnter data to be pushed inside the Stack 2: ");
					scanf("%d",&data);
					if(tos2==size1) printf("Stack overflow!");
                    else tos2 = pushtwo(arr,data,tos2);
					break;
			case 3:	if(tos1==-1) printf("\nStack Underflow!!");
					else tos1 = popone(arr,tos1);
					break;
			case 4:	if(tos2==size) printf("\nStack Underflow!!");
					else tos2 = poptwo(arr,tos2);
					break;
			case 5: if(tos1==-1) printf("\nStack Empty!!!");
					else printf("Peeking stack 1: %d",peekone(arr,tos1));
					break;
			case 6: if(tos2==size) printf("\nStack Empty!!!");
					else printf("Peeking stack 2: %d",peektwo(arr,tos2));
					break;
			case 0: return 0;
			default: printf("Wrong choice!");
		}
	}
}
	
