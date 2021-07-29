/*
BASIC ALGORITHM FOR TOWER OF HANOI (OF N DISKS):
(1) Shift (n-1) disks from source to auxiliary.
(2) Nth disk will be moved from source to destination.
(3) The remaining (n-1) disks will be moved from auxiliary to destination.
*/
#include <stdio.h>
void towerOfHanoi(int n, char source, char destination, char aux)
{
    if (n == 1){
        printf("\nMove disk 1 from rod %c to rod %c", source, destination);
        return;
    }
    towerOfHanoi(n-1, source, aux, destination);
    printf("\nMove disk %d from rod %c to rod %c", n, source, destination);
    towerOfHanoi(n-1, aux, destination, source);
}
/*
So when calling, the tOH() function will move the disk from the 2nd argument (source) to the 3rd argument (destination). The values of these two arguments needs to be changed as required. Now, as the steps are mentioned at the beginning of the program:
(1) towerOfHanoi(n-1, source, aux, destination); will shift (n-1) disks from source to auxiliary.
(2) printf("\nMove disk %d from rod %c to rod %c", n, source, destination); to move nth disk from source to destination.
(3) towerOfHanoi(n-1, aux, destination, source); to move the remaining (n-1) disks will be moved from auxiliary to destination.
CONCEPT OF TOP-DOWN AND BACKTRACKING:
Imagine a function:
func1(){
	func2(){
		func3()
		}
	}
Then func1->func2 & then func2->func3 is called Top-Down. After func3 is executed, func3->func1 is called backtracking.
For n disks in the Tower Of Hanoi puzzle, we will name 2^(n-1) number of topdowns and backtrackings.
*/

int main()
{
	int n,ch;
	while(1){
		printf("Enter number of disks: \n");
		scanf("%d",&n);
		towerOfHanoi(n, 'A', 'C', 'B');
		printf("\n----------------------------------");
		choice:
		printf("\nEnter again? (1 for yes, 2 for no): \n");
		scanf("%d",&ch);
		if(ch==1) continue;
		else if(ch==2) return 0;
		else {
				printf("Wrong choice\n");
				goto choice;
		}
	}		
}