
#include<stdio.h>
#include<stdlib.h>
#define item int
#define garb 87501579

typedef struct adt{
	item *arr;
	int f, r, size;
}DEQ;

void init(DEQ *q, int size){
	q->f = q->r = -1;
	q->size = size;
	q->arr = (item *)malloc(sizeof(item)*(q->size));
}


int isEmpty(DEQ *q){
	return (q->r == -1 && q->f == -1);
}


int isFull(DEQ *q){
	int fr = q->f-1, re = q->r+1;
	if(fr == -1) fr = q->size-1;
	if(re == q->size) re = 0;
	return (fr == q->r || re == q->f);
}

int isFull2(DEQ *q){
	return((q->f == q->r+1)||(q->f == 0 && q->r == q->size-1));
}

int enqueueRear(DEQ *q, item data){
	if(isFull(q)){
		printf("Queue Overflow!");
		return garb;
	}
	if(q->f == -1) q->f++;										
	if(q->r == q->size-1) q->r = 0;								
	else q->r++;
	q->arr[q->r] = data;
}


int enqueueFront(DEQ *q, item data){
	if(isFull(q)) { printf("Queue Overflow!"); return garb; }
	if(q->r == -1) q->r = q->size-1;							
	if(q->f == -1 || q->f == 0) q->f = q->size-1;				
	else q->f--;
	q->arr[q->f] = data;
}


item dequeueFront(DEQ *q){
	if(isEmpty(q)) { printf("Queue Underflow!"); return garb; }
	item data = q->arr[q->f];								
	if(q->f == q->r) q->r = q->f = -1;	
	else if(q->f == q->size-1) q->f = 0;
	else q->f++;
	return data;
}


item dequeueRear(DEQ *q){
	if(isEmpty(q)) { printf("Queue Underflow!"); return garb; }
	item data = q->arr[q->r];					
	if(q->f == q->r) q->r = q->f = -1;							
	else if(q->r == 0) q->r = q->size-1;				
	else q->r--;
	return data;
}


item peekFront(DEQ *q){
	if(isEmpty(q)) return garb;
	else return q->arr[q->f];
}

item peekRear(DEQ *q){
	if(isEmpty(q)) return garb;
	else return q->arr[q->r];
}


int main(){
	DEQ q;
	int n;
	printf("\nEnter the size of the Queue: ");
	scanf("%d",&n);
	printf("\nInitializing the Queue...");
	init(&q,n);
	while(1){
		printf("\nMENU:-----------------------------------------");
		printf("\nFRONT: %d, REAR: %d",q.f,q.r);
		printf("\n1: ENQUEUE FROM FRONT");
		printf("\n2: ENQUEUE FROM REAR");
		printf("\n3: DEQUEUE FROM FRONT");
		printf("\n4: DEQUEUE FROM REAR");
		printf("\n5: PEEK FROM FRONT");
		printf("\n6: PEEK FROM REAR");
		printf("\n0: EXIT");
		printf("\nEnter your choice: ");
		int ch;
		item data;
		scanf("%d",&ch);
		switch(ch){
			case 1: printf("\nEnter data to be enqueued from the front of queue: ");
					scanf("%d",&data);
					enqueueFront(&q,data);
					break;
			case 2: printf("\nEnter data to be enqueued from the rear of queue: ");
					scanf("%d",&data);
					enqueueRear(&q,data);
					break;
			case 3: data = dequeueFront(&q);
					if(data == garb) printf("\nCan't dequeue as Queue empty");
					else printf("\nDequeued element (From front): %d",data);
					break;
			case 4: data = dequeueRear(&q);
					if(data == garb) printf("\nCan't dequeue as Queue empty");
					else printf("\nDequeued element (From rear): %d",data);
					break;
			case 5: data = peekFront(&q);
					if(data == garb) printf("\nStack Empty!!!");
					else printf("Data at front: %d",data);
					break;
			case 6: data = peekRear(&q);
					if(data == garb) printf("\nStack Empty!!!");
					else printf("Data at rear: %d",data);
					break;
			case 0: return 0;
			default: printf("Wrong choice!");
		}
	}
	return 0;
}
