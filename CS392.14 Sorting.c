
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
	printf("%d and %d were swapped!\n",*x,*y);
}

void printArr(int *arr, int size){
	int i;
	printf("\n");
	for(i=0;i<size;i++) printf("%d ",arr[i]);
	printf("\n\n");
}

//---------------------------------------------------------------BUBBLE SORT--------------------------------------------------------------

void bubbleSort(int *arr, int size){
	int flag,i,j;
	for(flag=1,i=1; i<size && flag==1; i++){
		printf("\nFlag is 1. If flag is 0 loop stops.\n");
		for(flag=0,j=0; j<size-i; j++){
			printf("Pass %d: Comparing arr[%d] with all elements from arr[%d] to arr[%d] & placing in proper position..\n",i,j,j+1,size-1);
			printf("Flag is 0\n");
			if(arr[j]>arr[j+1]){
				printf("Flag is made to 1 as %d is greater than %d, and also ",arr[j],arr[j+1]);
				swap(&arr[j],&arr[j+1]);
				printArr(arr,size);
				flag = 1;
			}
		}
	}
}


//-----------------------------------------------------------LINEAR INSERTION SORT---------------------------------------------------------

void linInsSort(int *arr, int size){
	int i,j,temp;
	for(i=1;i<size;i++){
		printf("\ntemp = arr[%d] = %d\n", i, arr[i]);
		for(temp=arr[i],j=i-1; j>=0 && temp<arr[j]; j--){
			printf("temp = %d < arr[%d] = %d found!\nShifting...", temp, j, arr[j]);
			arr[j+1] = arr[j];
			printArr(arr,size);
		}
		printf("Inserting temp = %d in arr[%d]", temp, j+1);
		arr[j+1] = temp;
		printArr(arr,size);
		printf("Array is sorted from arr[0] to arr[%d]\n", i);
	}
}
/*


*/

//-----------------------------------------------------------BINARY INSERTION SORT---------------------------------------------------------

int binSearch(int *arr, int key, int lb, int ub) {
	int mid;
	if(lb<=ub) {
		mid=(lb+ub)/2;
		if (key==arr[mid]) return mid;
		else if (key<arr[mid]) return binSearch(arr,key,lb,mid-1);
		else if (key>arr[mid]) return binSearch(arr,key,mid+1,ub);
	}
	else return ub;
}

void binInsSort(int *arr, int size){
	int i,j,temp,pos;
	for(i=1;i<size;i++){
		pos = binSearch(arr,arr[i],0,i-1);
		for(temp=arr[i], j=i-1; j>pos; j--){
			arr[j+1] = arr[j];
			arr[j+1] = temp;
			printArr(arr,size);
		}
		printArr(arr,size);
	}
}


//-----------------------------------------------------------SELECTION SORT----------------------------------------------------------------

void selectionSort(int *arr, int size){
	int i,j,p;
	for(i=0;i<size-1;i++){
		printf("Pass %d: Searching smallest element between arr[%d] to arr[%d] and replacing with arr[%d]...\n",i+1,i,size-1,i);
		for(j=i+1,p=i; j<size; j++){
			printf("\nI:%d, P:%d, J:%d\n",arr[i],arr[p],arr[j]);
			if(arr[p]>arr[j]){
				printf("\nSince arr[J]:%d < arr[P]:%d, P = J [as P will hold lowest J value in a loop]\n",arr[j],arr[p]);
				p=j;
				printf("\nI:%d, P:%d, J:%d\n",arr[i],arr[p],arr[j]);
			}
		}
		if(p!=i){
			printf("\nSince %d is not equal to %d, and %d is required smallest element, ",arr[p],arr[i],arr[p]);
			swap(&arr[p],&arr[i]);
		}
		printArr(arr,size);
	}
}


//-------------------------------------------------------------SHELL SORT------------------------------------------------------------------

void shellSort(int *arr, int size){
	int i,j,temp,gap = size/2;
	printf("I = Gap, Gap = Size/2\n");
	while(gap>0){
		for(i=gap; i<size; i++){
			for(temp=arr[i],j=i-gap; j>=0 && temp<arr[j]; j=j-gap){
				printf("\nGAP:%d, I:%d, J:%d, temp: arr[I]: %d\n",gap,i,j,arr[i]);
				arr[j+gap] = arr[j];
				printf("Temp: %d < arr[J]: %d, so arr[J+Gap] = arr[J]",temp,arr[j]);
				printArr(arr,size);
				printf("J = J-Gap, [till J >= 0]. So now J: %d\n",j-gap);
			}
			printf("Since J=J-Gap gives J<0, J+Gap will give us initial J\n");
			printf("\nGAP:%d, I:%d, J:%d, temp: arr[I]: %d\n",gap,i,j,arr[i]);
			arr[j+gap] = temp;
			printf("J+Gap done and arr[J+Gap] = temp");
			printArr(arr,size);
			printf("I++ so I: %d\n",i+1);
		}
		gap = gap/2;
		printf("Gap is Gap/2\n");
	}
	printArr(arr,size);
	printf("Gap = 0 so loop terminates\n");
}


//---------------------------------------------------------------MERGE SORT----------------------------------------------------------------

void mergeSort(int *arr, int lb, int ub){
	int i, j, k, arr2[ub];
	printf("In this recursion, LB: %d, UB: %d\n",lb,ub);
	if(lb<ub){
		int mid = (lb+ub)/2;
		printf("MID: %d\n",mid);
		mergeSort(arr,lb,mid);
		printf("First half done. Now second half\n");
		mergeSort(arr,mid+1,ub);
		printf("Second half done\n");
		for(i=lb, j=mid+1, k=lb; i<=mid && j<=ub; ){
			printf("I: index for left array. J: index for right array. K: index for new sorted array\nElement will be placed in arr2[k]\n");
			printf("So I: LB(%d)->MID(%d), J: MID+1(%d)->UB(%d), K: LB(%d)\n",lb,mid,mid+1,ub,lb);
			if(arr[i]<arr[j]){
				arr2[k]=arr[i];
				printf("We have arr[i]: arr[%d]: %d < arr[j]: arr[%d]: %d\n",i,arr[i],j,arr[j]);
				printf("So arrnew[k] = arr[i]. Then k++ and i++. %d is added to arr2[k].\n",arr[i]);
				k++; i++;
				printf("Now i: %d, j: %d, k:%d\n",i,j,k);
			}
			else{
				arr2[k]=arr[j];	
				printf("We have arr[j]: arr[%d]: %d <= arr[i]: arr[%d]: %d\n",j,arr[j],i,arr[i]);
				printf("So arrnew[k] = arr[j]. Then k++ and j++. %d is added to arr2[k].\n",arr[j]);
				k++; j++;
				printf("Now i: %d, j: %d, k:%d\n",i,j,k);
			}
		}
		while(i<=mid){
			arr2[k++]=arr[i++];
			printf("Leftover arr[i] (left subpart) being copied to arr2\n");
			printf("Now i: %d, j: %d, k:%d\n",i,j,k);
		}
		while(j<=ub){
			arr2[k++]=arr[j++];
			printf("Leftover arr[j] (right subpart) being copied to arr2\n");
			printf("Now i: %d, j: %d, k:%d\n",i,j,k);
		}
		for(k=lb; k<=ub; k++){
			arr[k] = arr2[k];
			printf("Arr2 array being copied to original Arr array\n");
			printf("Now i: %d, j: %d, k:%d\n",i,j,k);
		}
		printArr(arr,ub+1);
	}
}	
		

//---------------------------------------------------------------QUICK SORT----------------------------------------------------------------

void quickSort(int *arr, int lb, int ub, int size){
	int pivot = arr[lb];
	int i,up = ub;
	int down = lb;
	printf("PIVOT:%d, LB:%d, UB:%d, DOWN:%d, UP:%d\n",pivot,arr[lb],arr[ub],arr[down],arr[up]);
	while(down<up){
		while(pivot<arr[up]) up--;
		while(pivot>=arr[down] && down<ub) down++;
		printf("DOWN++ till arr[DOWN] > PIVOT [DOWN < UB obviously], and UP-- till arr[UP] < PIVOT \n");
		printf("PIVOT:%d, LB:%d, UB:%d, DOWN:%d, UP:%d\n",pivot,arr[lb],arr[ub],arr[down],arr[up]);
		if(down<up){
			printf("Since %d is more than %d and %d is less than %d\n",arr[down],pivot,arr[up],pivot);
			swap(&arr[down],&arr[up]);
			printArr(arr,size);
			printf("PIVOT:%d, LB:%d, UB:%d, DOWN:%d, UP:%d\n",pivot,arr[lb],arr[ub],arr[down],arr[up]);
		}
	}
	printf("Now, UP>DOWN. So we will swap arr[LB] or PIVOT, and arr[UP]\n");
	swap(&arr[lb],&arr[up]);
	printArr(arr,size);
	if(lb<up-1) quickSort(arr,lb,up-1,size);
	if(up+1<ub) quickSort(arr,up+1,ub,size);
}


//---------------------------------------------------------------RADIX SORT----------------------------------------------------------------

int getMax(int arr[], int n){
    int i;
    int max = arr[0];
    for (i=1; i<n; i++){
        if (arr[i]>max) max = arr[i];
    }
    return max;
}

void radixSort(int arr[], int n){
	int i,digitPlace = 1;
	int result[n];
	int largestNum = getMax(arr,n);
	while(largestNum/digitPlace >0){
		int count[10] = {0};
		for (i=0; i<n; i++)
			count[(arr[i]/digitPlace)%10]++;
		for (i=1; i<10; i++)
			count[i] += count[i-1];
		for (i=n-1; i>= 0; i--){
			result[count[(arr[i]/digitPlace)%10]-1] = arr[i];
			count[(arr[i]/digitPlace)%10]--;
		}
		for (i=0; i<n; i++)
			arr[i] = result[i];
		digitPlace *= 10;
	}
}
/*

*/

//----------------------------------------------------------------------------------------------------------------------------------------

int main() {
	int siz,i,data;
	printf("Number of elements in array?: ");
	scanf("%d",&siz);
	int *array = (int *)malloc(siz*sizeof(int));
	for(i=0;i<siz;i++){
		printf("Enter element %d of array: ",i+1);
		scanf("%d",&array[i]);
	}
	while(1) {
		printf("\n===============================================================================\n");
		printf("MENU:\n");
		printf("  1.BUBBLE SORT\n");
		printf("  2.LINEAR INSERTION SORT\n");
		printf("  3.BINARY INSERTION SORT\n");
		printf("  4.SELECTION SORT\n");
		printf("  5.SHELL SORT\n");
		printf("  6.MERGE SORT\n");
		printf("  7.QUICK SORT\n");
		printf("  8.RADIX SORT\n");
		printf("  0.EXIT\n");
		printf("Your array: \n");
		printArr(array,siz);
		printf("Enter your choice: \n");
		int user_ch;
		scanf("%d", &user_ch);
		switch(user_ch) {
			case 1: bubbleSort(array,siz);
			break;
			case 2: linInsSort(array,siz);
			break;
			case 3: binInsSort(array,siz);
			break;
			case 4: selectionSort(array,siz);
			break;
			case 5: shellSort(array,siz);
			break;
			case 6: mergeSort(array,0,siz-1);
			break;
			case 7: quickSort(array,0,siz-1,siz);
			break;
			case 8: radixSort(array,siz);
			break;
			case 0: return 0;
			default: printf("Invalid! Choose again");
		}
	}
}
