
#include <stdio.h>
#include <stdlib.h>
#define item int


typedef struct avlnode{
	item data;
	struct avlnode *left, *right;
	int balance;
}avl;

int depth(avl *);
void setbalance(avl *);

avl* getNode(int data) {
	avl *newNode;
	newNode = (avl *)malloc(sizeof(avl));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->balance = 0;
	newNode->data = data;
	return newNode;
}

//-----------------------------------------------------AVL TREE SPECIAL FUNCTIONS---------------------------------------------------------

void leftrotate(avl **root){
	if(root == NULL) return;
	avl *temp, *rt = *root;
	temp = (*root)->right->left;
	(*root)->right->left = *root;
	*root = (*root)->right;
	(*root)->left->right = temp;
	setbalance(*root);
}

void rightrotate(avl **root){
	if(root == NULL) return;
	avl *temp, *rt = *root;
	temp = (*root)->left->right;
	(*root)->left->right = *root;
	*root = (*root)->left;
	(*root)->right->left = temp;
	setbalance(*root);
}

void setbalance(avl *root){
	if(root == NULL) return;
	root->balance = depth(root->left)-depth(root->right);
	if(root->left != NULL) setbalance(root->left);
	if(root->right != NULL) setbalance(root->right);
}

void balanceNode(avl **root){
	if(*root == NULL) return;
	setbalance(*root);
	if((*root)->balance > 1){
		if((*root)->left->balance < 0) 
			leftrotate(&(*root)->left);
		rightrotate(root);
	}
	else if((*root)->balance < -1){
		if((*root)->right->balance > 0)
			rightrotate(&(*root)->right);
		leftrotate(root);
	}
	else return;
}

//----------------------------------------------------------------------------------------------------------------------------------------

void preOrder(avl *root){
	if(root == NULL) return;
	else{
		printf("%d ",root->data);
		if(root->left != NULL)
			preOrder(root->left);
		if(root->right != NULL)
			preOrder(root->right);
	}
}

void inOrder(avl *root){
	if(root == NULL) return;
	else{
		if(root->left != NULL)
			inOrder(root->left);
		printf("%d ",root->data);
		if(root->right != NULL)
			inOrder(root->right);
	}
}

void postOrder(avl *root){
	if(root == NULL) return;
	else{
		if(root->left != NULL)
			postOrder(root->left);
		if(root->right != NULL)
			postOrder(root->right);
		printf("%d ",root->data);
	}
}

void create(avl **root, item data) {
	if(*root == NULL){
		*root = getNode(data);
		(*root)->left = (*root)->right = NULL;
	}
	else if(data < (*root)->data)
		create(&(*root)->left,data);
	else
		create(&(*root)->right,data);
	balanceNode(root);
}

avl* searchPrev(avl *root, item data){
	if(root == NULL) return NULL;
	else if(root->data == data || root->left->data == data || root->right->data == data) return root;
	else if(root->left->data > data) searchPrev(root->left, data);
	else if(root->right->data > data) searchPrev(root->right, data);
}

avl* inOrderSuccessor(avl *root){
	while(root->left != NULL)
		root = root->left;
	return root;
}

avl* inOrderPredecessor(avl *root){
	while(root->right != NULL)
		root = root->right;
	return root;
}

void del(avl **root, item data) {
	if(root == NULL) return;
	else if(data < (*root)->data)
		del(&((*root)->left),data);
	else if(data > (*root)->data)
		del(&((*root)->right),data);
	else{
		if((*root)->left == NULL && (*root)->right == NULL){
			free(*root);
			*root = NULL;
		}
		else if((*root)->left != NULL && (*root)->right == NULL){
			avl *t = *root;
			*root = (*root)->left;
			free(t);
		}
		else if((*root)->left == NULL && (*root)->right != NULL){
			avl *t = *root;
			*root = (*root)->right;
			free(t);
		}
		else if((*root)->left != NULL && (*root)->right != NULL){
			avl *t = inOrderSuccessor((*root)->right);
			(*root)->data = t->data;
			del(&(*root)->right, t->data);
		}
	}
}

int depth(avl *root){
    int d, d1, d2;
	if(root == NULL) return 0;
	d1 = depth(root->left);
	d2 = depth(root->right);
	d = ((d1>d2)?d1:d2)+1;  return d;
}
	
//------------------------------------------------------AVL TREE IMPLEMENTATION------------------------------------------------------------
int main() {
	avl *r = NULL;
	int data;
	while(1) {
		printf("\n===============================================================================\n");
		printf("MENU:\n");
		printf("  1.INSERTION\n");
		printf("  2.DELETION\n");
		printf("  3.TRAVERSAL\n");
		printf("  4.DEPTH\n");
		printf("  0.EXIT\n");
		printf("Enter your choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		switch(user_ch) {
			case 1: while(1){
						printf("Enter the data for the Node (0 to exit): ");
						scanf("%d", &data);
						if(data!=0) create(&r, data);
						else break;
					}
			break;
			case 2: printf("Enter the data for the Node to be deleted: ");
					scanf("%d", &data);
					del(&r, data);
					balanceNode(&r);
			break;
			case 3: printf("1: PreOrder, 2: InOrder, 3: PostOrder: ");
					scanf("%d", &data);
					if(data==1) preOrder(r);
					else if(data==2) inOrder(r);
					else if(data==3) postOrder(r);
					else printf("Wrong input");
			break;
			case 4: printf("Depth of binary search tree is: %d",depth(r));
			break;
			case 0: return 0;
			default: printf("Wrong Input! Try Again.\n\n");
			break;
		}
	}
}