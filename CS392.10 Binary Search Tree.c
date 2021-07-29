#include <stdio.h>
#include <stdlib.h>
#define item int

typedef struct bstnode{
	item data;
	struct bstnode *left, *right;
}bstree;

bstree* getNode(data) {
	bstree *newNode;
	newNode = (bstree *)malloc(sizeof(bstree));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	return newNode;
}

void preOrder(bstree *root){
	if(root == NULL) return;
	else{
		printf("%d ",root->data);
		if(root->left != NULL)
			preOrder(root->left);
		if(root->right != NULL)
			preOrder(root->right);
	}
}

void inOrder(bstree *root){
	if(root == NULL) return;
	else{
		if(root->left != NULL)
			inOrder(root->left);
		printf("%d ",root->data);
		if(root->right != NULL)
			inOrder(root->right);
	}
}

void postOrder(bstree *root){
	if(root == NULL) return;
	else{
		if(root->left != NULL)
			postOrder(root->left);
		if(root->right != NULL)
			postOrder(root->right);
		printf("%d ",root->data);
	}
}

void create(bstree **root, item data) {
	if(*root == NULL){
		*root = getNode(data);
		(*root)->left = (*root)->right = NULL;
	}
	else if(data < (*root)->data)
		create(&(*root)->left,data);
	else
		create(&(*root)->right,data);
}

bstree* searchPrev(bstree *root, item data){
	if(root == NULL) return NULL;
	else if(root->data == data || root->left->data == data || root->right->data == data) return root;
	else if(root->left->data > data) searchPrev(root->left, data);
	else if(root->right->data > data) searchPrev(root->right, data);
}

bstree* findMin(bstree *root){
	while(root->left != NULL)
		root = root->left;
	return root;
}

void del(bstree **root, item data) {
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
			bstree *t = *root;
			*root = (*root)->left;
			free(t);
		}
		else if((*root)->left == NULL && (*root)->right != NULL){
			bstree *t = *root;
			*root = (*root)->right;
			free(t);
		}
		else if((*root)->left != NULL && (*root)->right != NULL){
			bstree *t = findMin((*root)->right);
			(*root)->data = t->data;
			del(&(*root)->right, t->data);
		}
	}
}
/*
*/

int depth(bstree *root){
	if(root == NULL) return 0;
	int d1 = depth(root->left);
	int d2 = depth(root->right);
	int d = (d1>d2)?d1:d2;
	return d+1;
}
/*
int search(bstree *root, int z){
	bstree *temp = root;
	if(root == NULL) return 0;
	else{
		if(z = root->left->data) printf("%d is the left child of %d",z,root->data);
		else if(z = root->right->data) printf("%d is the right child of %d",z,root->data);
		else printf("Data not found");
		if(root->left != NULL)
			preOrder(root->left);
		if(root->right != NULL)
			preOrder(root->right);
	}
}
*/

int nodeCount(bstree *root){
	if (root == NULL) return 0;     
    return(nodeCount(root->left) + 1 + nodeCount(root->right));
}
	
//-------------------------------------------------------BST IMPLEMENTATION---------------------------------------------------------------
int main() {
	bstree *r = NULL;
	int data;
	while(1) {
		printf("\n===============================================================================\n");
		printf("MENU:\n");
		printf("  1.INSERTION\n");
		printf("  2.DELETION\n");
		printf("  3.TRAVERSAL\n");
		printf("  4.DEPTH AND NODE COUNT\n");
		printf("  5.SEARCH\n");
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
			case 2: if(r == NULL){
						printf("Tree empty");
						break;
					}
					printf("Enter the data for the Node to be deleted: ");
					scanf("%d", &data);
					del(&r, data);
			break;
			case 3: if(r == NULL){
						printf("Tree empty");
						break;
					}
					printf("1: PreOrder, 2: InOrder, 3: PostOrder: ");
					scanf("%d", &data);
					if(data==1) preOrder(r);
					else if(data==2) inOrder(r);
					else if(data==3) postOrder(r);
					else printf("Wrong input");
			break;
			case 4: printf("Depth of binary tree is: %d",depth(r));
					printf("\nNumber of nodes: %d",nodeCount(r));
			break;
			case 5: printf("Enter the data to be searched: ");
					scanf("%d", &data);
					//search(r,data);
			break;
			case 0: return 0;
			default: printf("Wrong Input! Try Again.\n\n");
			break;
		}
	}
	return 0;
}

