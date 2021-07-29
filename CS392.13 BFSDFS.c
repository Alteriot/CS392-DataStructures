
#include<stdio.h>
#include<stdlib.h>
#define item int
#define garb -9999

//------------------------------------------------SUPPORTING STACK AND QUEUE FUNCTIONS-------------------------------------------------------
typedef struct adt{
	item *arr;
	int size, TOS;
}stack;
void initS(stack *s, int n){
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

typedef struct adt1{
	item *arr;
	int f, r, size;
}DEQ;
void init(DEQ *q, int size){
	q->f = q->r = -1;
	q->size = size;
	q->arr = (item *)malloc(sizeof(item)*(q->size));
}
int isEmptyQ(DEQ *q){
	return (q->r == -1 && q->f == -1);
}
int isFullQ(DEQ *q){
	return((q->f == q->r+1)||(q->f == 0 && q->r == q->size-1));
}
int enqueue(DEQ *q, item data){
	if(isFullQ(q)) { printf("Queue Overflow!"); return garb; }
	if(q->f == -1) q->f++;										//If queue empty, then f = r = -1.
	if(q->r == q->size-1) q->r = 0;								//If queue not full but somehow r = size-1 (but front is empty).
	else q->r++;
	q->arr[q->r] = data;
}
item dequeue(DEQ *q){
	if(isEmptyQ(q)) { printf("Queue Underflow!"); return garb; }
	item data = q->arr[q->f];									//Store last element in data.
	if(q->f == q->r) q->r = q->f = -1;							//If this was the last element in queue, set r & f both to -1 when dequeued.
	else if(q->f == q->size-1) q->f = 0;						//If f = size-1 (end of queue) we can't do f++. So set f to 0.
	else q->f++;
	return data;
}
item peekFront(DEQ *q){
	if(isEmptyQ(q)) return garb;
	else return q->arr[q->f];
}

//----------------------------------------------------------------------------------------------------------------------------------------

void dfs(int **arr, int size){
	int flag[size], i, j;
	for(i=0; i<size; i++) flag[i] = 0;
	stack s;
	initS(&s, size);
	i = 0;
	push(&s, i);
	while(!isEmpty(&s)){
		int vertex = pop(&s);
		if(flag[vertex] == 0){
			flag[vertex] = 1;
			printf("%d ",vertex);
			for(j=0;j<size;j++){
				if(arr[vertex][j] == 1 && flag[j] == 0) push(&s,j);
			}
		}
	}
}

void bfs(int **arr, int size){
	int flag[size], i, j;
	for(i=0; i<size; i++) flag[i] = 0;
	DEQ q;
	init(&q, size);
	i = 0;
	enqueue(&q, i);
	while(!isEmptyQ(&q)){
		int vertex = dequeue(&q);
		if(flag[vertex] == 0){
			flag[vertex] = 1;
			printf("%d ",vertex);
			for(j=0;j<size;j++){
				if(arr[vertex][j] == 1 && flag[j] == 0) enqueue(&q,j);
			}
		}
	}
}

int main(){
	int i, j, n;
	FILE *fp;
	fp = fopen("graph.txt", "r");
	if(fp == NULL){
		printf("File not found!");
		return 0;	
	}
	fscanf(fp, "%d ", &n);
	int **graph = (int **)calloc(n, sizeof(int*));
	for(i = 0; i < n; i++){
		graph[i] = (int *)calloc(n, sizeof(int));
		for(j = 0; j < n; j++){
			fscanf(fp, "%d ", &graph[i][j]);
		}
	}
	printf("\nAdjacency Matrix: \n");
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%d\t", graph[i][j]);
		}
		printf("\n");	
	}	
	while(1) {
		printf("\n===============================================================================\n");
		printf("MENU:\n");
		printf("1.BREADTH FIRST SEARCH\n2.DEPTH FIRST SEARCH\n0.EXIT\nEnter choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		switch(user_ch) {
			case 1: printf("BFS: "); bfs(graph, n);
			break;
			case 2: printf("DFS: "); dfs(graph, n);
			break;
			case 0: return 0;
		}
	}
}
