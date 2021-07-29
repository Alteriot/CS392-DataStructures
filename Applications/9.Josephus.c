/*
CIRCULAR LINKED LIST is a non contiguous collection of elements. It is linear, i.e. every element has only one successor and one predecessor, but unlike array, the elements are non-contiguous. We don't have NULL pointers here, except in an empty list.
A Linked list is made up or several nodes, with each node having the data part and the link part. The data part stores data, whereas the link part stores the address of the next node. Binary searching is impossible in linked list. The last node's link stores the first node's address. The head is always the FIRST INSERTED NODE, and rear is THE LAST INSERTED NODE.
Example: Address[Data|Link]
0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x4000]-->0x4000[40|0x5000]-->0x5000[50|0x1000]
So here, if we declare node *NODE;
HEADER = 0x1000, REAR = 0x5000. REAR->link will always point to head.
If we take the first node;
NODE->link = *NODE.link = 0x2000, NODE->data = *NODE.data = 10.
If we do NODE = NODE->link, then NODE = 0x2000, NODE->link = *NODE.link = 0x3000, NODE->data = *NODE.data = 20.
*/

#include <stdio.h>
#include <stdlib.h>
#define item int
#define garb 333

typedef struct linked_list {
	int data;
	struct linked_list *link;
}node;
/*
A linked list structure has two parts. The "item data" part will store the data of the specified datatype. The *link part will hold the address of the next node (A node is a structure, as in, item + address, and not ONLY item or ONLY address).
So, the link part must be a pointer to a structure. This type of structure, holding a pointer of the same type, is called self referential structure. 
Here, a structure linked_list has been declared and a node of type linked_list has been declared.
-------------------------------------------------------------
When we will say node *nd1 = nd2;
(1) nd2 must be an address of a node/node pointer (Like either some node->link, or header).
(2) nd1 will hold nd2's address.
(3) nd1->link will be nd2->link. [NOTE: This is temp1->link and not temp1.link. temp1->link is same as *temp1.link]
(4) nd1->data will be nd2->data.
-------------------------------------------------------------
When we will say node *nd1;
(1) nd1 will hold some node's address.
(2) You must make a node named nd1 later using nd1 = (node*)malloc(sizeof(node))
(3) The address of this node will now be contained by nd1.
(4) Say, 1000[10|0x2000] is a node. nd1 = 0x1000. nd1->link = *nd1.link = 0x2000. nd1->data = *nd1.data = 10. [*nd1.data is invalid in C].
-------------------------------------------------------------
*/

node* makeNode();
node* getCurrent(node *, int);
node* getPrevious(node *, int);
void insBeginCList(node **, node **, int);
void insAtCList(node *, int, int);
void appendCList(node **, int);
int delBeginCList(node **, node**);
int delAtCList(node *, int);
void deleteList(node **);
void display(node *);
int search(node *, int);
int length1(node *, node *);
int length2(node *);
/*
Function makeNode() will create a node [Data + Pointer].
Function getCurrent() will return the current position or index of a node.
Function getPrevious() will return the position or index of the previous node.
Function display() will display the entire linked list.
Function insAfter() will insert a node after the nth node.
Function insBegin() will insert a node at the start of the linked list.
Function append() will insert a node at the end of the linked list.
Function search() will return the position or index of a particular data.
*/

node* makeNode() {
	node *newNode;
	newNode = (node *)malloc(sizeof(node));
	newNode->link = newNode;
	return newNode;
}
/*
(1) Make a node pointer.
(2) Allocate memory via malloc.
(3) Set link part of the node to itself. The node points to itself now (as this is circular linked list).
(4) Return node's address.
*/

node* getCurrent(node *head, int pos) {
	node *temp = head;
	int count = 1;
	do{						
		if(count == pos) return temp;
		temp = temp->link;
		count++;
	}while(temp != head);
	return NULL;
}
/*
(1) A pointer-to-node/node pointer is created and it's named as temp.
(2) The header (address of 1st node), is stored in temp.
(3) Count is initialised to one. Count will keep track of the position of the node (Number of times loop is running = node number).
(4) The link of the last node is head. So when temp = head then the end of linked list has been reached.
(5) While the end has not been reached, if count is not equal to pos, then move to next node's link by temp = temp->link and increase count by 1.
(6) Imp: Here, a do while loop is required, as if we did while(temp!->head){blablabla} then it won't go inside the loop as temp is already initialised to head. It needs to go inside the loop, and then temp will change to head->link. After that the condition while(temp!->head) will hold valid because once temp has changed to the 2nd node (next node of head), NOW, whenever temp comes back to being head again, it will mean that temp has done traversing the entire node circularly.
EXAMPLE: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x4000]-->0x40000[40|0x1000]. Say, I want address of 3rd node. Pos = 3.
(6) temp = head = 0x1000, temp->link = 0x2000. count = 1. (temp points to 1st node)
(7) In the next iteration temp = 0x2000, temp->link = 0x3000. count = 2. (temp points to 2nd node)
(8) In the next iteration temp = 0x3000, temp->link = 0x4000. count = 3. (temp points to 3rd node)
(9) Now as count = pos = 3, we return temp (Here, 0x3000). This is the address of the 3rd node.
(10) The link part will point to the NEXT element. So if we insert here it will be AFTER the current node. (?)
Here, temp is address of this node and temp->link is also address (Of next node). So temp = temp->link.
ALGORITHM: To get address of the (pos)th element.
(a) Start with 1st element, initialize count = 1.
(b) Traverse each node, count++.
(c) When count = pos, return node.
*/

node* getPrevious(node *head, int pos) {
	node *temp = head;
	int count = 1;
	printf("a");
	while(temp->link != head) {
		if(count == pos-1) return temp;
		temp = temp->link;
		count++;
	}
	return NULL;
}
/*
(1) A pointer-to-node/node pointer is created and it's named as temp.
(2) The header (address of 1st node), is stored in temp.
(3) Count is initialised to one. Count will keep track of the position of the node.
(4) The link of the last node is head. So when temp = head then the end of linked list has been reached.
(5) While the end has not been reached, if count is not equal to pos, then move to next node's link by temp = temp->link and increase count by 1.
EXAMPLE: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x4000]-->0x40000[40|0x1000].
(6) temp = head = 0x1000, temp->link = 0x2000. count = 1. (temp->link points to 2nd node)
(7) In the next iteration temp = 0x2000, temp->link = 0x3000. count = 2. (temp->link points to 3rd node)
(8) In the next iteration temp = 0x3000, temp->link = 0x4000. count = 3. (temp->link points to 4th node)
(9) While the end has not been reached, if count = the position-1, then return the temp. If temp->link = NULL, then return NULL.
(10) Since we are moving one node ahead, we will be getting the address of the previous node here.
Here, temp is address of this node and temp->link is also address (Of next node). So temp = temp->link.
ALGORITHM: To get address of the (pos)th element.
(a) Start with 1st element, initialize count = 1.
(b) Traverse each node, count++.
(c) When count = pos-1, return node.
*/

//--------------------------------------------------------INSERTION FUNCTIONS---------------------------------------------------------------

void insBeginCList(node **head, node **rear, int data){
	node *newNode = makeNode();
	newNode->data = data;
	if(*head == NULL){
		newNode->link = newNode;
		*rear = newNode;
	}
	else{
		newNode->link = *head;
		(*rear)->link = newNode;
	}
	*head = newNode;
}		
/*
(0) If *head is used as lvalue (LHS of an assignment statement. Here, *head = newNode is done) then function must be called with **head. Head must be used as lvalue here because the head will get changed (since node is being added before header, the address of the new node will be the new header).
(1) A pointer-to-node/node pointer is created and it's named as newNode.
(3) node *newNode = makeNode(); Here, makeNode() returns newNode, or, the address of the node made from makeNode().
(4) The link part of node-pointed-by-newNode will contain the contents of the earlier header file. The data part will contain the data.
(5) The rear points to the head (as this is a circular linked list), so, rear->link = head. This also needs to be updated to the new head otherwise it will store the old head.
EXAMPLE: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x4000]-->0x4000[40|0x1000]. Head: 222[0x1000]. 222 is address, 0x1000 is content.
(5) The first node initially was 0x1000[10|0x2000] and now a new node 0x500[d|x] is to be put at the beginning. d = Data, x = Link.
(6) So, the address of the old 1st-node, 0x1000, will be copied to the link of the new 1st-node with the help of newNode->link = *head;
(7) If we had typed newNode->link = head, then, ???
(8) So now, node = 0x500[d|1000].
(9) The data part of the new node, d, is made via newNode->data = data. This data is to be passed as a parameter. Say, we passed 7.
(10) *head = newNode: I am adding a node in the beginning so the beginning address or header of the whole linked list should be changed.
(11) So now, node = 0x500[7|0x1000], where head = 0x500, head->data = 7, head->link = 0x1000.
ALGORITHM: To insert a node at the beginning of a linked list:
(a) First make a node (store its address in 'newnode').
(b) Copy the header of linked list to newnode->link.
(c) Copy the data to newnode->data.
(d) Set the address of the newnode as new header of linked list.
*/

void insAtCList(node *head, int pos, int data) {
	node *curr = getPrevious(head, pos);
	node *temp = makeNode();
	temp->data = data;
	if(pos < 1 || curr == NULL) return;
	temp->link = curr->link;
	curr->link = temp;
}
/*
(1) A node pointer stores the address (returned by getCurrent()) of the head, and the pos (position after which data is to be inserted).
(2) If pos < 1 or curr = NULL then invalid position, therefore return.
(3) Else, make a node (via makeNode()). makeNode returns the address of the newly made node; store the address in a node pointer temp.
(4) Necessary assignments done.
EXAMPLE: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x5000]-->0x5000[50|NULL] and node 0x4000[40|y] to be inserted after 3rd node.
(5) The node 0x4000[d|x] is made via makeNode() and address 0x4000 is stored in temp. So now temp->data = d and temp->link = NULL.
(6) getCurrent() takes the pos and returns the address of the node at pos, so it returns 0x3000 here. So, curr = 0x3000.
(7) temp->data = data; Data to be put inside the node is passed in the function through the parameter; it's 40. So temp->data = 40.
(8) temp->link = curr->link. As curr = 0x3000, so curr->link = 0x5000. So temp->link = 0x5000.
(9) curr->link = temp. As temp is 0x4000 (address of newly made node) so curr->link = 0x4000. Thus our node is 0x4000[40|0x5000].
(10) 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x4000]-->0x4000[40|0x5000]-->0x5000[50|NULL].
ALGORITHM: To insert a node at the beginning of a linked list:
(a) First make a node (store its address in 'newnode'). It is to be inserted after 'pos' position.
(b) Get the address of pos-th node via getCurrent(). See getCurrent's algorithm. Store the address in node pointer curr.
(c) If valid position, then make a new node via makeNode (see makeNode's algorithm) and store its position in node pointer temp.
(d) Set data part of the node pointed by temp as 'data'.
(e) Set link part of the node pointed by temp as the address of the (pos+1)-th node stored in curr->link. (curr has pos-th node's address).
(f) Set link part of the node pointed by curr as the address of the newly made node 'temp'. (curr has pos-th node's address).
*/

void appendCList(node **rear, int data){
	node *temp = makeNode();
	temp->data = data;
	if(*rear == NULL) temp->link = temp;
	else{
		temp->link = (*rear)->link;
		(*rear)->link = temp;
	}
	*rear = temp;
}
/*
(0) If *head is used as lvalue (LHS of an assignment statement. Here, *head == NULL is done) then function must be called with **head.
(1) First check if linked list has anything in it. If it's empty, then head will be NULL, then insertBegin() will be called. No return?? 
(2) Why not (head == NULL)?
(3) Else, make a node (via makeNode()). makeNode returns the address of the newly made node; store the address in a node pointer newNode.
(4) Store the header address in a node pointer temp.
(5) Necessary assignments done.
EXAMPLE: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x4000]-->0x4000[40|NULL] and node 0x5000[d|y] to be inserted at the end.
(6) The node 0x5000[d|y] is made via makeNode() and address 0x5000 is stored in newNode. So now newNode->data = d and newNode->link = y.
(7) The address of the header of the linked list is stored in temp.
(8) What would've happened if we wrote temp = *head?
(9) The data provided as argument is copied inside newNode->data. Here it's 50. So now, newNode->data is 50.
(10) Since this is append function, the node is to be added at the end. So traverse through the entire list until temp->link becomes NULL.
(11) In the example, when temp->link becomes NULL (3rd node), temp becomes 3000, and temp->data = 40. temp->link = NULL obviously.
(12) temp->link = newNode. As newNode = 0x5000, so temp->link = 0x5000. So our node at 0x4000 is now 0x4000[40|0x5000].
(13) Thus, we get: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x4000]-->0x4000[40|0x5000]-->0x5000[50|NULL]
ALGORITHM: To insert a node at the end of a linked list:
(a) If it's an empty linked list, call insertBegin().
(b) First make a node (store its address in 'newnode'). Store the header address of the linked list in temp.
(c) Data is stored in the "data" field of node pointed by newNode, aka, newNode->data.
(d) Traverse the link (by doing temp = temp->link) until the end node is encountered (when temp->link becomes NULL).
(e) Store the last node's address in newNode pointer.
*/

//--------------------------------------------------------DELETION FUNCTIONS---------------------------------------------------------------

int delBeginCList(node **head, node**rear){
	if(*rear == NULL) return 1;
	else{
		node *temp = (*rear)->link;
		(*rear)->link = ((*rear)->link)->link;
		*head = temp->link;
		free(temp);
		return 0;
	}
}
/*
(0) If *head is used as lvalue (LHS of an assignment statement. Here, *head == NULL is done) then function must be called with **head.
(1) EXAMPLE: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|NULL]. Here, head = 0x1000, head->data = 10, head->link = 0x2000.
(2) A node pointer temp is created, and *temp = *head is done. So, now, temp = 0x1000, temp->data = 10 and temp->link = 0x2000.
(3) *head = *head->link is done. Now, head = 0x2000. temp = 0x1000 still.
(4) free(temp) is done, so the node pointed by temp (node at 0x1000) was deleted or freed.
(5) free(pointer_to_datatype) is a function which deletes the data pointed by pointer_to_datatype.
ALGORITHM: To delete the first node of a linked list:
(a) If it's an empty linked list, return.
(b) Header needs to be shifted to the next node.
(c) Node needs to be freed by free().
*/

int delAtCList(node *head, int pos){
	node *p = getPrevious(head,pos);
	if(p->link == NULL) return 1;
	else{
		node *temp = p->link;
		p->link = temp->link;
		free(temp);
		return 0;
	}
}
/*
(1) EXAMPLE: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|NULL]. Here, head = 0x1000, head->data = 10, head->link = 0x2000.
(2) Assuming 2nd node 0x2000[20|0x3000] is to be deleted. So 2nd node is target.
(3) p = getPrevious() is done, so now, p = 0x1000, p->link = 0x2000, p->data = 10. [Since p will store previous node of the target node].
(4) If p->link is NULL (Which means the prev node of target, is actually the last node) then no deletion possible.
(5) Else, node pointer temp is created, and *temp = p->link is done. So, now, temp = 0x2000, temp->data = 20 and temp->link = 0x3000.
(6) p->link = temp->link is done. Now, p->link = 0x3000. temp = 0x2000 still.
(7) free(temp) is done, so the node pointed by temp (node at 0x2000) was deleted or freed.
ALGORITHM: To delelte any node at a given position:
(a) Get the address of the (target-1)th node by getPrevious(). getPrevious() travers the entire node, from head, until it reaches (target-1).
(b) Store the address of the node before the target node at node pointer p.
(c) If invalid target, return 1.
(d) Make a temp. node pointer which will point to the target node, by doing *temp = p->link. (p is the prev node, so p->link holds target).
(e) Now p->link must be updated, to store the address of the NODE NEXT to the target node. So p->link = temp->link is done.
(f) The target node is freed using free().
*/

void deleteList(node **head){
	node *temp = *head;
	do{
		temp = (temp)->link;
		free(temp);
	}while(temp != *head);
}
/*
*/

//--------------------------------------------------------DISPLAY FUNCTIONS----------------------------------------------------------------

void display(node *head) {
    int nodeno = 1;
	node *temp = head;
	do{
		printf("Node %d: %p\tNode->data: %d\tNode->link: %p\n",nodeno,temp,temp->data,temp->link);
		nodeno++;
		temp = temp->link;
	}while(temp != head);
}
/*
(1) While header is not NULL, or while the linked list is not end (when linked list ends then link will become NULL):
(2) Print the head->data and continue traversing from one node to another by head = head->link; and nodeno++; and keep on printing the elements.
*/

int search(node *head, item data) {
	node *temp = head;
	int count = 1;
	do{
		if(temp->data == data)
			return count;
		temp = temp->link;
		count++;
	}while(temp != NULL);
	return 0;
}
/*
(1) A pointer-to-node/node pointer is created and it's named as temp.
(2) The header (address of 1st node), is stored in temp.
(3) Count is initialised to one. Count will keep track of the position of the node.
(4) NULL is the link of the last node. So when temp = NULL then the end of linked list has been reached.
(5) While the end has not been reached, if count is not equal to pos, then move to next node's link by temp = temp->link and increase count by 1.
EXAMPLE: 0x1000[10|0x2000]-->0x2000[20|0x3000]-->0x3000[30|0x4000]-->0x4000[40|NULL].
(6) temp = head = 0x1000, temp->link = 0x2000. count = 1. (temp points to 1st node)
(7) In the next iteration temp = 0x2000, temp->link = 0x3000. count = 2. (temp points to 2nd node)
(8) In the next iteration temp = 0x3000, temp->link = 0x4000. count = 3. (temp points to 3rd node)
(9) While the end has not been reached, if count = the position entered, then return the count. If temp = NULL, then return 0.
(10) The DIFFERENCE BETWEEN SEARCH() AND GETCURRENT(): getCurrent() returns address but search() returns position of a node.
Here, temp is address of this node and temp->link is also address (Of next node). So temp = temp->link.
*/

int length1(node *head, node *temp){
    if(temp->link==head) return 1;
    return 1+length1(head,temp->link);
}

int length2(node *head){
    static node *temp = head;
    temp = temp->link;
    if (temp == head)
        return 1;
    return 1 + length2(head);
}
/*
Length of linked list using recursion. head->link calls the function from the next node. IT continues until head becomes NULL (last node).
*/

node* Josephus(node *head, int k){
    int i;
	while(head->link != head){
		for(i=1; i<k-1; i++) head = head->link;
		node *temp = head->link;
		head->link = temp->link;
		free(temp);
		head = head->link;
		display(head);
	}
	return head;
}
//-----------------------------------------------------------MAIN FUNCTION------------------------------------------------------------------

int main() {
	node *head = NULL, *rear = NULL;
	int data, pos, x, Jnum;
	while(1) {
		printf("===============================================================================\n");
		printf("MENU:\n");
		printf("  1.INSERT AT BEGINNING\n");
		printf("  2.INSERT IN MIDDLE\n");
		printf("  3.INSERT AT THE END (APPEND)\n");
		printf("  4.DELETE AT BEGINNING (DELETE HEADER)\n");
		printf("  5.DELETE IN MIDDLE\n");
		printf("  6.JOSEPHUS\n");
		printf("  7.LENGTH OF LINKED LIST\n");
		printf("  8.SEARCH A DATA\n");
		printf("  9.DISPLAY THE LIST\n");
		printf("  0.EXIT\n");
		printf("Enter your choice: ");
		int user_ch;
		scanf("%d", &user_ch);
		printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
		switch(user_ch) {
			case 1: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					insBeginCList(&head, &rear, data);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 2: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					printf("Enter the position at which you want to insert (can't be negative or 0): ");
					scanf("%d", &pos);
					if(pos > length2(head) || pos < 1){
						printf("Position invalid. Insertion unsuccessful!");
						printf("x");
                    }
					else insAtCList(head, pos, data);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 3: printf("Enter the data for the Node: ");
					scanf("%d", &data);
					appendCList(&rear, data);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 4: printf("Data being deleted... \n");
					x = delBeginCList(&head,&rear);
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 5: printf("Enter the position of the data to be removed: ");
					scanf("%d", &pos);
					if(pos > length2(head))
						printf("Position out of bound. Deletion unsuccessful!");
					else {
					printf("Data being deleted... \n");
					x = delAtCList(head,pos);
					if(x==1) printf("Deletion unsuccessful!\n");
					}
					printf("\n\nHead: %p, Tail: %p\n\n",head,rear);
			break;
			case 6: printf("Enter skip value: \n"); scanf("%d",&Jnum);
					Josephus(head,Jnum);
			break;
			case 7: printf("Calculating length... \n");
					x = length2(head);
					printf("Length is: %d \n",x);
			break;
			case 8: printf("Enter the data to be searched in the List: ");
					scanf("%d", &data);
					pos = search(head, data);
					if(pos == 0) printf("Element not found in List.\n");
					else printf("Element found in List. Position: %d\n", pos);
			break;
			case 9: if(head == NULL) printf("The List is Empty.\n");
					else {
						printf("The Linked List:\n\n");
						display(head);
					}
					printf("\n");
			break;
			case 0: printf("Exiting Program......\n\n"); return 0;
			break;
			default: printf("Wrong Input! Try Again.\n\n");
			break;
		}
	}
	return 0;
}
