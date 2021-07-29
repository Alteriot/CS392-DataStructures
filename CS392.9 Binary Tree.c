
#include<stdio.h>
#include<stdlib.h>
#define item int
#define garb -99129

//------------------------------------------------------STACK FUNCTIONS (FOR FUTURE USE)---------------------------------------------------
typedef struct stackNode {
	item data;
	struct stackNode *link;
}snode;

snode* makeNode() {
	snode *newNode;
	newNode = (snode *)malloc(sizeof(snode));
	newNode->link = NULL;
	return newNode;
}

void push(snode **head, item data) {
	snode *newNode = makeNode();
	newNode->link = *head;
	newNode->data = data;
	*head = newNode;
}

item pop(snode **head){
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

//--------------------------------------------------------------BINARY TREE FUNCTIONS-------------------------------------------------------

typedef struct binaryTreeNode{
	item data;
	struct binaryTreeNode *left, *right;
}bitnode;

bitnode* getNode(item);
bitnode* makeMyTree(bitnode*);
void dispTree();
void preOrder(bitnode*);
void preOrderNonRec();
void inOrder(bitnode*);
void inOrderNonRec();
void postOrder(bitnode*);
void postOrderNonRec();

bitnode* getNode(item data) {
	bitnode *newNode;
	newNode = (bitnode *)malloc(sizeof(bitnode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	return newNode;
}

bitnode* makeMyTree(bitnode *root){
	item data, ldata, rdata;
	printf("Node data: ");
	scanf("%d",&data);
	bitnode* newNode = getNode(data);
	printf("Node[%d]'s left node present? (0: No): ",data);
	scanf("%d",&ldata);
	if(ldata!=0){
		bitnode* newNodeL = getNode(ldata);
		newNodeL = makeMyTree(newNodeL);
		newNode->left = newNodeL;
	}
	printf("Node[%d]'s right node present? (0: No): ",data);
	scanf("%d",&rdata);
	if(rdata!=0){
		bitnode* newNodeR = getNode(rdata);
		newNodeR=makeMyTree(newNodeR);
		newNode->right = newNodeR;
	}
	return newNode;
}

void del(bitnode **root, int data){
	if(root == NULL) return;
}

//--------------------------------------------------------------TRAVERSAL FUNCTIONS--------------------------------------------------------

void preOrder(bitnode *root){
	if(root == NULL) return;
	else{
		printf("%d ",root->data);
		if(root->left!=NULL) preOrder(root->left);
		if(root->right!=NULL) preOrder(root->right);
	}
}

void inOrder(bitnode *root){
	if(root == NULL) return;
	else{
		if(root->left!=NULL) inOrder(root->left);
		printf("%d ",root->data);
		if(root->right!=NULL) inOrder(root->right);
	}
}

void postOrder(bitnode *root){
	if(root == NULL) return;
	else{
		if(root->left!=NULL) postOrder(root->left);
		if(root->right!=NULL) postOrder(root->right);
		printf("%d ",root->data);
	}
}

/*
void preOrderNonRec(bitnode *root){			//NOT WORKING
	snode *s;
	//init(&s,100); if we did array implementation of stack.
	while(root!=NULL){
		printf("%d ",root->data);
		if(root->right!=NULL) push(&s,root->right->data);
		if(root->left!=NULL) root = root->left;
		else root->data = pop(&s);
	}
}

void inOrderNonRec(bitnode *root){			//NOT WORKING
	snode *s;
	while(1){
		while(root!=NULL){
			push(&s,root->data);
			root = root->left;
		}
		if(*root == NULL) break; //if(isEmpty(&s)) break; if we did array implementation of stack
		else{
			root->data = pop(&s);
			printf("%d ",root->data);
			root = root->right;
		}
	}
}

void postOrderNonRec(bitnode *root){			//NOT WORKING
	snode *s,*f;
	do{
		while(root!=NULL){
			push(&s,root->data);
			push(&f,0);
			root = root->left;
		}
		if(*root == NULL) break;//if(isEmpty(&)) break; if we did array implementation of stack
		else{
			flag = pop(&f);
			if(flag == 0){
				push(&f,1);
				root = (peek(&s))->right;
			}
			else{
				root->data = pop(&s);
				printf("%d ",root->data);
				root = NULL;
			}
		}
	}
}
*/

void displayMyTree(bitnode *root){		//NOT WORKING	
	while(root!=NULL){
		printf("%d[%d %d]\n",root->data, root->left->data, root->right->data);
		displayMyTree(root->left);
		displayMyTree(root->right);
	}
}

int depth(bitnode *root){
	if(root == NULL) return 0;
	int d1 = depth(root->left);
	int d2 = depth(root->right);
	int d = (d1>d2)?d1:d2;
	return d+1;
}

int nodeCount(bitnode *root){
	if (root == NULL) return 0;     
    return(nodeCount(root->left) + 1 + nodeCount(root->right));
}

//-----------------------------------------------------------------------------------------------------------------------------------------

int main(){
	bitnode *root = NULL;
	int data, x;
	while(1) {
		printf("\n===============================================================================\n");
		printf("MENU:\n");
		printf("  1.MAKE TREE\n");
		printf("  2.DELETE NODE (X)\n");
		printf("  3.DELETE FULL TREE (X)\n");
		printf("  4.DEPTH AND NODE COUNT\n");
		printf("  5.TRAVERSAL\n");
		printf("  6.SEARCH (x)\n"); //Will take x as input and print "x is the right/left child of a" or "x is the root node".
		printf("  0.EXIT\n");
		printf("Enter your choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		switch(user_ch) {
			case 1: root = makeMyTree(root);
			break;
			case 4: printf("Depth of binary tree is: %d",depth(root));
					printf("\nNumber of nodes: %d",nodeCount(root));
			break;
			case 5: printf("1: Pre Order Traversal, 2: In Order Traversal, 3: Post Order Traversal. Enter: ");
					scanf("%d",&data);
					if(data == 1) preOrder(root);
						//printf("Non recursive way: "); preOrderNonRec(root);
					else if(data == 2) inOrder(root);
						//printf("Non recursive way: "); inOrderNonRec(root);
					else if(data == 3) postOrder(root);
						//printf("Non recursive way: "); postOrderNonRec(root);
					else printf("Wrong Option");
			break;
			case 6: printf("Node[Left Right]: \n");
					displayMyTree(root);
			break;
			case 0: return 0;
		}
	}
}
		

