/*
LINKED LIST REPRESENTATION OF POLYNOMIALS: Two data part, one containing constant and other containing power. One link part.
Example: (4x^3)+(11x^2)+7 will be stored as:
0x1000[4|3|0x2000]-->0x2000[11|2|0x3000]-->0x3000[7|0|NULL]
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list_poly {
	int con, pow;
	struct linked_list_poly *link;
}node;

node* makeNode();
node* getCurrent(node *, int);
node* getPrevious(node *, int);
void insBegin(node **, int, int);
void append(node **, int, int);
void displayPol(node *);
void insertionSortDesc(node **);
node* polyAdd(node *, node *);
node* polySub(node *, node *);
node* polyMul(node *, node *);
node* polyDiv(node *, node *);
node* makePoly(node *, int);

node* makeNode() {
	node *newNode;
	newNode = (node *)malloc(sizeof(node));
	newNode->link = NULL;
	return newNode;
}

node* getCurrent(node *head, int pos) {
	node *temp = head;
	int count = 1;
	while(temp != NULL) {
		if(count == pos) return temp;
		temp = temp->link;
		count++;
	}
	return NULL;
}

node* getPrevious(node *head, int pos) {
	node *temp = head;
	int count = 1;
	while(temp->link != NULL) {
		if(count == pos-1)
			return temp;
		temp = temp->link;
		count++;
	}
	return NULL;
}

void insBegin(node **head, int cons, int power) {
	node *newNode = makeNode();
	newNode->link = *head;
	newNode->con = cons;
	newNode->pow = power;
	*head = newNode;
}

void append(node **head, int cons, int power) {
	if(*head == NULL) {
		insBegin(head, cons, power);
		return;
	}
	node *newNode = makeNode(), *temp = *head;
	newNode->con = cons;
	newNode->pow = power;
	while(temp->link != NULL) {
		temp = temp->link;
	}
	temp->link = newNode;
}

void displayPol(node *head) {
	while(head != NULL) {
		printf("%dx%d ",head->con,head->pow);
		head = head->link;
	}
}

void deleteList(node **head){
	node *temp;
	while(*head != NULL){
		temp = *head;
		*head = (*head)->link;
		free(temp);
	}
}

void insertionSortDesc(node **head){
	node *outPrev, *outCurr, *inPrev, *inCurr;
	for(outPrev = *head, outCurr = (*head)->link; outCurr != NULL;  )
	{
		for(inCurr = *head, inPrev = NULL; outCurr->pow < inCurr->pow && inCurr != outCurr; inPrev = inCurr, inCurr = inCurr->link);
		if(inCurr == outCurr){
			outPrev = outPrev->link;
			outCurr = outCurr->link;
			}
		else {
			if(inPrev!=NULL){
				outPrev->link = outCurr->link;
				outCurr->link = inCurr;
				inPrev->link = outCurr;
				outCurr = outPrev->link;
				}
			else{
				outPrev->link = outCurr->link;
				outCurr->link = inCurr;
				*head = outCurr;
				outCurr = outPrev->link;
			}
		}
	}
}
//-------------------------------------------------------POLYNOMIAL FUNCTIONS---------------------------------------------------------------

node* polyAdd(node *L1, node *L2){
	node *L3 = NULL;
	while(L1!=NULL && L2!=NULL){
		if(L1->pow > L2->pow){
			append(&L3,L1->con,L1->pow);
			L1 = L1->link;
		}
		else if(L2->pow > L1->pow){
			append(&L3,L2->con,L2->pow);
			L2 = L2->link;
		}
		else if(L2->pow == L1->pow){
			append(&L3,((L1->con)+(L2->con)),L2->pow);
			L1 = L1->link;
			L2 = L2->link;
		}
	}
	while(L2!=NULL){
		append(&L3,L2->con,L2->pow);
		L2 = L2->link;
	}
	while(L1!=NULL){
		append(&L3,L1->con,L1->pow);
		L1 = L1->link;
	}
	return L3;
}
/*
ALGORITHM:
(1) First we have to SORT the polynomials (Sort using node->pow in descending order). Assuming previously sorted.
(2) Declare node pointer poly1 to point to 1st polynomial, poly2 to point to 2nd polynomial, poly3 to point to the result.
(3) If power of poly1 matches with power of poly2 (poly1->pow == poly2->pow), then add the coefficients (poly->cons) and store the result in head3. Keep the powers unchanged. Append the newly made node in poly3.
(4) If power doesn't match, simply append the node in poly3.
(5) Move on to the next term of the polynomials by poly = poly->link.
(6) Don't move on both poly1 and poly2 at once, move only on the polynomial whose term has just been appended.
(6) If one of the polynomials end, keep on continuing with the other polynomial (append one by one, no need to add) until node = NULL.
(8) Return the address of the result polynomial poly3.
*/

node* polySub(node *L1, node *L2){
		node *L3 = NULL;
	while(L1!=NULL && L2!=NULL){
		if(L1->pow > L2->pow){
			append(&L3,L1->con,L1->pow);
			L1 = L1->link;
		}
		else if(L2->pow > L1->pow){
			append(&L3,L2->con,L2->pow);
			L2 = L2->link;
		}
		else if(L2->pow == L1->pow){
			append(&L3,((L1->con)-(L2->con)),L2->pow);				//NOT CORRECT.
			L1 = L1->link;
			L2 = L2->link;
		}
	}
	while(L2!=NULL){
		append(&L3,L2->con,L2->pow);
		L2 = L2->link;
	}
	while(L1!=NULL){
		append(&L3,L1->con,L1->pow);
		L1 = L1->link;
	}
	return L3;
}
/*
ALGORITHM:
(1) First we have to SORT the polynomials (Sort using node->pow in descending order). Assuming previously sorted.
(2) Declare node pointer poly1 to point to 1st polynomial, poly2 to point to 2nd polynomial, poly3 to point to the result.
(3) If power of poly1 matches with power of poly2 (poly1->pow == poly2->pow), then subtract the coefficients (poly->cons) and store the result in head3. Keep the powers unchanged. Append the newly made node in poly3.
(4) If power doesn't match, simply append the node in poly3. Use appropriate sign while doing so.
(5) Move on to the next term of the polynomials by poly = poly->link.
(6) Don't move on both poly1 and poly2 at once, move only on the polynomial whose term has just been appended.
(6) If one of the polynomials end, keep on continuing with the other polynomial (append one by one, no need to add) until node = NULL.
(8) Return the address of the result polynomial poly3.
*/

node* polyMul(node *L1, node *L2){
	node *L3 = NULL, *t = NULL, *L;
	while(L2!=NULL){
		L = L1;
		while(L!=NULL){
			append(&t,(L2->con)*(L->con),(L2->pow)+(L->pow));
			L=L->link;
			}
		node *L3cpy = L3;
		L3 = polyAdd(t,L3);
		deleteList(&t);
		L2 = L2->link;
		deleteList(&L3cpy);
		}
	return L3;
}

//-----------------------------------------------------POLYNOMIAL CONSTRUCTION--------------------------------------------------------------
node* makePoly(node *head, int polno){
	int user_ch1, termno = 1, cons, power;
	while(1){
		printf("======================================================\n");
		printf("MENU : POLYNOMIAL CONSTRUCTION:\n");
		printf("  1.APPEND\n");
		printf("  2.DISPLAY THE POLYNOMIAL\n");
		printf("  0.EXIT FROM MENU 1\n");
		printf("Enter your choice: ");
		scanf("%d", &user_ch1);
		switch(user_ch1) {
			case 1: printf("Enter the constant part of the term %d of polynomial %d: ",termno,polno);
					scanf("%d", &cons);
					printf("Enter the exponent part of the term %d of polynomial %d: ",termno,polno);
					scanf("%d", &power);
					append(&head, cons, power);
					insertionSortDesc(&head);
					termno++;
			break;
			case 2: if(head == NULL) printf("The List is Empty.\n");
					else {
						printf("Polynomial (Descending sorted):\n\n");
						displayPol(head);
					}
					printf("\n");
			break;
			case 0: polno++; return head;
			break;
			default: printf("Wrong Input! Try Again.\n\n");
			break;
		}
	}
}
	
//----------------------------------------------------------MAIN FUNCTION-------------------------------------------------------------------
int main() {
	node *head1 = NULL, *head2 = NULL, *head3 = NULL;
	int cons, power, pos, x;
	printf("======================================================\n");
	printf("POLYNOMIAL 1:\n");
	head1 = makePoly(head1,1);
	printf("======================================================\n");
	printf("POLYNOMIAL 2:\n");
	head2 = makePoly(head2,2);
	while(1) {
		printf("======================================================\n");
		printf("MENU 2: POLYNOMIAL FUNCTIONS:\n");
		printf("  1.ADD\n");
		printf("  2.SUBTRACT\n");
		printf("  3.MULTIPLY\n");
		printf("  4.DIVIDE\n");
		printf("  5.MAKE TWO OTHER POLYNOMIALS\n");
		printf("  0.EXIT\n");
		printf("Enter your choice: ");
		int user_ch2;
		scanf("%d", &user_ch2);
		switch(user_ch2) {
			case 1: head3 = polyAdd(head1,head2);
					printf("\t"); displayPol(head2); printf("\n"); printf("+");
					printf("\t"); displayPol(head1); printf("\n");
					printf("________________________________________\n");
					printf("\t"); displayPol(head3);
			break;
			case 2: head3 = polySub(head1,head2);
					printf("\t"); displayPol(head2); printf("\n"); printf("-");
					printf("\t"); displayPol(head1); printf("\n");
					printf("________________________________________\n");
					printf("\t"); displayPol(head3);
			break;
			case 3: head3 = polyMul(head1,head2);
					printf("\t"); displayPol(head2); printf("\n"); printf("*");
					printf("\t"); displayPol(head1); printf("\n");
					printf("________________________________________\n");
					printf("\t"); displayPol(head3);
			break;
			case 4:
			break;
			case 5: main();
			break;
			case 0: return 0;
			break;
			default: printf("Wrong Input! Try Again.\n\n");
			break;
		}
	}
}
