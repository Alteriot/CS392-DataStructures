#include<stdio.h>
#include<conio.h>

void Swap0(int a, int b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void Swap1(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Swap2(int **a, int **b){
	int *temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Swap3(int **a, int **b){
	int *temp;
	temp = **a;
	**a = **b;
	**b = *temp;
}

void Swap4(int *a, int *b){
	int *temp;
	temp = a;
	a = b;
	b = temp;
}
/*
Q. Swap0() IS INCORRECT. IT WONT SWAP ANY VALUE. WHY?
ANS: One structure (or structure variable) is stored in the main(). When we call by value i.e. Swap0(int a, int b):
(1) We are copying those contents from main() to func().
(2) Changes are being done inside func() and not main() [Swap0(), Swap1() etc. are func() here, they are changing values, NOT the main() function].
(3) Then func() exits and deletes whatever was stored inside (here, the copied content).
(4) The changes are NOT being copied from func() to main().
Thus, the value of variables is getting changed within the Swap0() function, but is remaining unchanged within the main() function.
MAIN[____(s)____]------>FUNC[____(s)____] ==========>> MAIN[____(s)____]------>FUNC[____(s_new)____] [If we call by value].

Q. Swap1() IS CORRECT. IT WILL SWAP VALUES. WHY?
One structure (or structure variable) is stored in the main(). When we call by reference i.e. Swap1(int *a, int *b):
(1) We are copying those content's address from main() to func().
(2) Changes are being done inside THE ADDRESS POINTED BY func() [which is, in main()].
(3) Then func() exits and deletes whatever was stored inside. (here, the address)
(4) The changes are thus being done directly on main().
Thus, the value of variables is getting changed within the main() function.
MAIN|____(s)____|------>FUNC|____(*s)____| ==========>> MAIN|____(s_new)____|<------FUNC|____(*s)____| [If we call by reference].
"S" inside main() container is getting changed in the second case (only when we pass address of the variable), not in the first case.
This is because when we are passing ADDRESS, we are telling the function to change the CONTENTS of THAT ADDRESS (Which is inside main() function) but when we pass value, we are just simply asking to change the COPIED VALUE (copied from main() to func()).

Q. Swap2() WILL SWAP ADDRESSES OF A AND B INSTEAD OF VALUES. WHY?

Q. Swap4() WILL DO NOTHING. WHY?
*/

int main(){
	int m,n,*p,*q;
	printf("Enter 1st value: ");
	scanf("%d",&m);
	printf("Enter 2nd value: ");
	scanf("%d",&n);
	printf("\nInitial address of m is %p and n is %p",&m,&n);
	p = &m;
	q = &n;
	Swap0(m,n);
	printf("\nAfter Swap0, 1st value: %d and 2nd value: %d",m,n);
	printf("\nAfter Swap0, 1st address: %p and 2nd address: %p",&m,&n);
	Swap1(&m,&n);
	printf("\nAfter Swap1, 1st value: %d and 2nd value: %d",m,n);
	printf("\nAfter Swap1, 1st address: %p and 2nd address: %p",&m,&n);
	Swap2(&p,&q);
	printf("\nAfter Swap2, 1st value: %d and 2nd value: %d",m,n);
	printf("\nAfter Swap2, 1st address: %p and 2nd address: %p",&m,&n);
	Swap3(&p,&q);
	printf("\nAfter Swap3, 1st value: %d and 2nd value: %d",m,n);
	printf("\nAfter Swap3, 1st address: %p and 2nd address: %p",&m,&n);
	Swap4(&m,&n);
	printf("\nAfter Swap4, 1st value: %d and 2nd value: %d",m,n);
	printf("\nAfter Swap4, 1st address: %p and 2nd address: %p",&m,&n);
	getch();
	return 0;
}
	
