/*
Various number representations in Sign magnitude form, 1's, 2's complement form (For an imaginary 3 bit number system:)
	S.M.	1's		2's
000 = 0		0		0		
001 = 1		1		1
010 = 2		2		2
011 = 3		3		3
100 = -0	-3		-4
101 = -1	-2		-3
110 = -2	-1		-2
111 = -3	-0		-1	-> 2's complement form is thus chosen as there's no concept of "-0" in it.
Thus, if binary number X denotes decimal number Y, then 2's complement of X will denote decimal number -Y.
*/
#include<stdio.h>
int main(){
	int i;
	printf("Enter value of i: ");
	scanf("%d",&i);
	char *p = (char*)&i;
//LHS: char *p -> Pointer to a character type variable.
//RHS: &i -> Address of an integer.
//RHS: (char*)&i -> We typecast &i such that it can be contained by a character pointer. 
//IF we wrote char *p = &i then there would be error as i is integer and p can only store character address.
/*
Here, p is declared as char pointer. So when p++, pointer will shift 1 byte (as it's char pointer, sizeof char = 1).
But, i is still an integer. So any pointer holding i's address will be an integer pointer.
If p was declared an integer pointer [int *p] then we could've written int *p = &i, but then again increasing p would have shifted 4 bytes as sizeof int is 4 (Or 2).
Thus, we typecasted &i to char so that, a character pointer *p can hold i (an integer)'s address.
EFFECT? Now if we do p++ it will shift 1 byte instead of 4 bytes at once, as p is a now a char pointer, as chars occupy 1 byte.
*/
//==========================================================================================================================================
	printf("%d ",(int)*p);
//==========================================================================================================================================
/*WHAT IS (int)*p:
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 256, output: 0.
/*
REASON: 256 = 1 0000 0000. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0000 [As it is requiring 4 bytes = 32 bits or digits. C compiler requires 4 bytes to store int]. Now, we focus on the last two bytes storing [0000 0001] and [0000 0000]. The lower byte (last byte or rightmost byte) is stored first in little endian machines and the upper byte (first byte or leftmost byte) is stored first in big endian machines.
Now when we are accessing *p (Char *p is a character pointer as declared, remember? So it will access 1 byte at a time, unlike integer pointers which access 4 bytes), we will be getting 0 or [0000 0000] or the last byte in a little endian machine.
If we do p++, then the next bit will be accessed and we will be getting 1 or [0000 0001] (See below when p++ is done) in little endian.
NOTE: Here, 2's complement is not being calculated. WHY?
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -2, output: -2.
/*
REASON: -2 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+2 = 0000 0000  0000 0000  0000 0000  0000 0010. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1111 1101) + 1 = 1111 1111  1111 1111  1111 1111  1111 1110.
This is requiring 4 bytes (32 bits or digits) to store as C compiler takes 4 bytes for int.
Now, the second last byte is storing [1111 1111] and the last byte is storing [1111 1110] -> lower byte. The lower byte (rightmost byte) is stored first in little endian machines and the upper byte (first byte or leftmost byte) is stored first in big endian machines.
Now when we are accessing *p (Char *p is a character pointer as declared, remember? So it will access 1 byte at a time, unlike integer pointers which access 4 bytes), we will be getting [1111 1110] or the last byte which is basically 2's of [0000 0010] or 2's of +2. So this is basically -2 [2's of +2 is -2]. Thus -2 is getting printed.
*******************************************************************************************************************************
WHY IS 2'S BEING CALCULATED FOR CERTAIN NUMBERS AND NOT BEING CALCULATED FOR CERTAIN OTHERS?
The leftmost bit of the first byte indicates if its a negative number (See the chart at the top of the program). Here the rightmost byte is 1111 1110. Or, ->1<-111 1110. The leftmost digit is 1. So, 2's will be done do evaluate the negative number.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 255, output: -1.
/*
REASON: 255 = 1111 1111. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1111 1111.
In the same logic above, 1111 1111 is actually the 2's of 0000 0001, which is +1, so 1111 1111 is basically -1. Thus we get -1.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 254, output: -2.
/*
REASON: 254 = 1111 1110. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1111 1110.
In the same logic above, 1111 1110 is actually the 2's of 0000 0010, which is +2, so 1111 1110 is basically -2. Thus we get -2.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 1, output: 1.
/*
REASON: 1 = 0000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  0000 0001.
In the same logic above, the pointer points to the byte stored first; i.e. 0000 0001, which is decimal 1, and we get 1 as a result.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 128, output: -128.
/*
REASON: 128 = 1000 0000. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1000 0000.
Pointer points to the last bit: 1000 0000, is actually the 2's of 1000 0000, which is 128, so 1000 0000 is basically -128. Thus we get -128.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 127, output: 127.
/*
REASON: 127 = 0111 1111. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  0111 1111.
The pointer points to the byte stored first; i.e. 0111 1111, which is decimal 127, and we get 127.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 129, output: -127.
/*
REASON: 129 = 1000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1000 0001.
In the same logic above, 1000 0001 is actually the 2's of 0111 1111, which is +127, so 1000 0001 is basically -127. Thus we get -127.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 257, output: 1.
/*
REASON: 257 = 1 0000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0001.
The char pointer is pointing towards the rightmost bit, 0000 0001 is actually binary of 1. Thus we get 1.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 260, output: 4.
/*
REASON: 260 = 1 0000 0100. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0100.
The char pointer is pointing towards the rightmost bit, 0000 0100 is actually the binary of 4. Thus we get 4.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -16, output: -16
/*
REASON: -16 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+16 = 0000 0000  0000 0000  0000 0000  0001 0000. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1110 1111) + 1 = 1111 1111  1111 1111  1111 1111  1111 0000.
The char pointer is pointing towards the rightmost bit, 1111 0000, which is actually the 2's of 0001 0000 (or +16) so this is -16.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -, output: 
/*
REASON: -16 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+2 = 0000 0000  0000 0000  0000 0000  0000 0010. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1111 1101) + 1 = 1111 1111  1111 1111  1111 1111  1111 1110.
*/
//==========================================================================================================================================
	printf("%u ",(int)*p);
//==========================================================================================================================================
//If i: 256, output: 0.
/*
REASON: 256 = 1 0000 0000. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0000 [As it is requiring 4 bytes = 32 bits or digits. C compiler requires 4 bytes to store int]. Now, we focus on the last two bytes storing [0000 0001] and [0000 0000] -> lower byte.  The lower byte (or rightmost byte) is stored first in little endian machines and the upper byte (or leftmost byte) is stored first in big endian machines.
Now when we are accessing *p (Char *p is a character pointer as declared, remember? So it will access 1 byte at a time, unlike integer pointers which access 4 bytes), we will be getting 0 or [0000 0000] or the lower byte in a little endian machine.
If we do p++, then the next bit will be accessed and we will be getting 1 or [0000 0001] (See below when p++ is done) in little endian.
NOTE: %u and %d makes no difference in case of positive numbers (See the chart at the beginning of the program), as sign bit is 0 in both cases. Sign bit is further expanded to 0, which makes no change in the number (look below to see what happens if sign bit is 1).
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -2, output: 4,294,967,294
//NOTE: Range of unsigned int: 0 to 65,535 in 2 bytes, 0 to 4,294,967,295 in 4 bytes.
/*
REASON: -2 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+2 = 0000 0000  0000 0000  0000 0000  0000 0010. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1111 1101) + 1 = 1111 1111  1111 1111  1111 1111  1111 1110.
This is requiring 4 bytes (32 bits or digits) to store as C compiler takes 4 bytes for int.
Now, the second last byte is storing [1111 1111] and the last byte is storing [1111 1110] -> lower byte. The lower byte (rightmost byte) is stored first in little endian machines and the upper byte (first byte or leftmost byte) is stored first in big endian machines.
Now when we are accessing *p (Char *p is a character pointer as declared, remember? So it will access 1 byte at a time, unlike integer pointers which access 4 bytes), we will be getting [1111 1110] or the last byte. Unlike last time, this is UNSIGNED [%u] thus 2's complement won't be calculated here. The direct decimal equivalent of 1111 1110 is 254 and so the output should be 254.

HOWEVER: We are getting output 4,294,967,294 which is basically the decimal of [1111.....10] thirty one 1s and one 0 (which is again the 2's of -2, or the number actually getting stored in the memory). WHY?
See the rightmost byte of 32 bit 2's: 1111 1110. This is getting stored as it is. The first sign bit (->1<-111 1110) or 1 is then getting expanded all over the other bytes. So we are getting [1111 1111  1111...... 1111 1110]. This is binary of 4,294,967,294.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 255, output: 4,294,967,295
/*
REASON: 255 = 1111 1111. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1111 1111.
The output 4,294,967,295 is actually [1111 1111...1111] thirty two 1.
See the rightmost byte of 32 bit 2's: 1111 1111. This is getting stored as it is. The first sign bit (->1<-111 1111) or 1 is then getting expanded all over the other bytes. So we are getting [1111 1111  1111...... 1111 1111]. This is binary of 4,294,967,295.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 254, output: 4,294,967,294
/*
REASON: 254 = 1111 1110. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1111 1110.
The output 4,294,967,294 is actually [1111 1111...1110] thirty one 1 and one 0.
See the rightmost byte of 32 bit 2's: 1111 1110. This is getting stored as it is. The first sign bit (->1<-111 1110) or 1 is then getting expanded all over the other bytes. So we are getting [1111 1111  1111...... 1111 1110]. This is binary of 4,294,967,294.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 1, output: 1
/*
REASON: 1 = 0000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  0000 0001.
In the same logic above, the pointer points to the byte stored first; i.e. 0000 0001, and we get 1 as a result. %u & %d same for +ve nos.
The sign bit (leftmost bit of a byte) of the 1st byte is 0, which when further expanded, give more 0, so the number remain unchanged.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 128, output: 4,294,967,168
/*
REASON: 128 = 1000 0000. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1000 0000.
The output 4,294,967,168 is actually [1111 1111...1000 0000] twenty four 1 and seven 0.
See the rightmost byte of 32 bit 2's: 1000 0000. This is getting stored as it is. The first sign bit (->1<-000 0000) or 1 is then getting expanded all over the other bytes. So we are getting [1111 1111  1111...... 1000 0000]. This is binary of 4,294,967,168.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 127, output: 127
/*
REASON: 127 = 0111 1111. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  0111 1111.
The pointer points to the byte stored first; i.e. 0111 1111, and we get 127 as a result. %u & %d same for +ve nos.
The sign bit (leftmost bit of a byte) of the 1st byte is 0, which when further expanded, give more 0, so the number remain unchanged.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 129, output: 4,294,967,169
/*
REASON: 129 = 1000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1000 0001.
The output 4,294,967,168 is actually [1111 1111...1000 0001] twenty four 1 and six 0 and one 1.
See the rightmost byte of 32 bit 2's: 1000 0001. This is getting stored as it is. The first sign bit (->1<-000 0001) or 1 is then getting expanded all over the other bytes. So we are getting [1111 1111  1111...... 1000 0001]. This is binary of 4,294,967,169.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 257, output: 1
/*
REASON: 255 = 1 0000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0001.
The rightmost bit, 0000 0001 is actually binary of 1. Thus we get 1.
The sign bit (leftmost bit of the a byte) of the 1st byte is 0, which when further expanded, give more 0, so the number remain unchanged.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 260, output: 4
/*
REASON: 260 = 1 0000 0100. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0100.
The rightmost bit, 0000 0100 is actually binary of 4. Thus we get 4.
The sign bit (leftmost bit of the a byte) of the 1st byte is 0, which when further expanded, give more 0, so the number remain unchanged.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -16, output: 4,294,967,280
/*
REASON: -16 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+16 = 0000 0000  0000 0000  0000 0000  0001 0000. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1110 1111) + 1 = 1111 1111  1111 1111  1111 1111  1111 0000.
The char pointer is pointing towards the rightmost bit, 1111 0000. Sign bit here is ->1<-111 0000 or 1 (the rightmost part of the leftmost byte). This bit gets expanded to all the other 15 bits and the output comes as 1111 1111  1111 1111  1111 1111  1111 0000. This is the binary of 4,294,967,280 thus it's getting printed. This is %u so 2's complement won't be applied here.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -, output: 
/*
REASON: -16 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+2 = 0000 0000  0000 0000  0000 0000  0000 0010. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1111 1101) + 1 = 1111 1111  1111 1111  1111 1111  1111 1110.
*/
//==========================================================================================================================================
	p++;
//==========================================================================================================================================
	printf("%d ",(int)*p);
//==========================================================================================================================================
//If i: 256, output: 1.
/*
REASON: 256 = 1 0000 0000. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0000 [As it is requiring 4 bytes = 32 bits or digits. C compiler requires 4 bytes to store int]. Now, we focus on the last two bytes storing [0000 0001] and [0000 0000] -> lower byte.  The lower byte (rightmost byte) is stored first in little endian machines and the upper byte (leftmost byte) is stored first in big endian machines.
Now when we are accessing *p (Char *p is a character pointer as declared, remember? So it will access 1 byte at a time, unlike integer pointers which access 4 bytes), we will be getting 0 or [0000 0000] or the lower byte in a little endian machine.
If we do p++, then the next byte will be accessed and we will be getting 1 or [0000 0001]. Thus we are getting 1 here.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -2, output: -1.
/*
REASON: -2 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+2 = 0000 0000  0000 0000  0000 0000  0000 0010. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1111 1101) + 1 = 1111 1111  1111 1111  1111 1111  1111 1110.
This is requiring 4 bytes (32 bits or digits) to store as C compiler takes 4 bytes for int.
Now, the second last byte is storing [1111 1111] and the last byte is storing [1111 1110] -> lower byte. The lower byte (rightmost byte) is stored first in little endian machines and the upper byte (leftmost byte) is stored first in big endian machines.
Now when we are accessing *p (Char *p is a character pointer as declared, remember? So it will access 1 byte at a time, unlike integer pointers which access 4 bytes), we will be getting [1111 1110] for p. Now we did p++ so it will move further one byte and point to the next byte [1111 1111]. This is basically 2's of [0000 0001] or 2's of +1. Thus, -1 is getting displayed.
*******************************************************************************************************************************
WHY IS 2'S BEING CALCULATED FOR CERTAIN NUMBERS AND NOT BEING CALCULATED FOR CERTAIN OTHERS?
The leftmost bit of the first byte indicates if its a negative number (See the chart at the top of the program). Here the rightmost byte is 1111 1110. Or, ->1<-111 1110. The leftmost digit is 1. So, 2's will be done do evaluate the negative number.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 255, output: 0
/*
REASON: 255 = 1111 1111. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1111 1111.
When we are doing p++ then the second to the rightmost byte is getting accessed, i.e. 0000 0000.
In the same logic above, 0000 0000 is 0. Thus we get 0.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 254, output: 0
/*
REASON: 254 = 1111 1110. This number is stored in binary as: 0000 0000  0000 0000  0000 0000  1111 1110.
When we are doing p++ then the second to the rightmost byte is getting accessed, i.e. 0000 0000.
In the same logic above, 0000 0000 is 0. Thus we get 0.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 1, output: 0
/*
REASON: 1 = 0000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0000 0000 0001.
When we are doing p++ then the second to the rightmost byte is getting accessed, i.e. 0000 0000.
In the same logic above, 0000 0000 is 0. Thus we get 0.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 128, output: 0
/*
REASON: 128 = 1000 0000. This number is stored in binary as: 0000 0000  0000 0000  0000 0000 1000 0000.
When we are doing p++ then the second to the rightmost byte is getting accessed, i.e. 0000 0000.
In the same logic above, 0000 0000 is 0. Thus we get 0.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 127, output: 0
/*
REASON: 127 = 0111 1111. This number is stored in binary as: 0000 0000  0000 0000  0000 0000 0111 1111.
When we are doing p++ then the second to the rightmost byte is getting accessed, i.e. 0000 0000.
In the same logic above, 0000 0000 is 0. Thus we get 0.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 129, output: 0
/*
REASON: 129 = 1000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0000 1000 0001.
When we are doing p++ then the second to the rightmost byte is getting accessed, i.e. 0000 0000.
In the same logic above, 0000 0000 is 0. Thus we get 0.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 257, output: 1
/*
REASON: 257 = 1 0000 0001. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0001.
When we are doing p++ then the second to the rightmost byte is getting accessed, i.e. 0000 0001.
In the same logic above, 0000 0001 is 1. Thus we get 1.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 260, output: 1
/*
REASON: 260 = 1 0000 0100. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0100.
When we are doing p++ then the second to the rightmost byte is getting accessed, i.e. 0000 0001.
In the same logic above, 0000 0001 is 1. Thus we get 1.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -16, output: -1
/*
REASON: -16 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+2 = 0000 0000  0000 0000  0000 0000  0000 0010. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1111 1101) + 1 = 1111 1111  1111 1111  1111 1111  1111 1110.
The char pointer is pointing towards the 2nd rightmost bit, 1111 1111, which is actually the 2's of 0000 0001 (or +1) so this is -1.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -, output: 
/*
REASON: -16 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+2 = 0000 0000  0000 0000  0000 0000  0000 0010. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1111 1101) + 1 = 1111 1111  1111 1111  1111 1111  1111 1110.
*/
//==========================================================================================================================================
	printf("%u ",(int)*p);
//==========================================================================================================================================
//If i: 256, output: 1.
/*
REASON: 256 = 1 0000 0000. This number is stored in binary as: 0000 0000  0000 0000  0000 0001  0000 0000 [As it is requiring 4 bytes = 32 bits or digits. C compiler requires 4 bytes to store int]. Now, we focus on the last two bytes storing [0000 0001] and [0000 0000] -> lower byte.  The lower byte (rightmost byte) is stored first in little endian machines and the upper byte (leftmost byte) is stored first in big endian machines.
Now when we are accessing *p (Char *p is a character pointer as declared, remember? So it will access 1 byte at a time, unlike integer pointers which access 4 bytes), we will be getting 0 or [0000 0000] or the lower byte in a little endian machine.
If we do p++, then the next byte will be accessed and we will be getting 1 or [0000 0001]. Thus we are getting 1 here.
NOTE: %u and %d makes no difference in case of positive numbers (See the chart at the beginning of the program).
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -2, output 4,294,967,295
//NOTE: Range of unsigned int: 0 to 65,535 in 2 bytes, 0 to 4,294,967,295 in 4 bytes.
/*
REASON: -2 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+2 = 0000 0000  0000 0000  0000 0000  0000 0010. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1111 1101) + 1 = 1111 1111  1111 1111  1111 1111  1111 1110.
This is requiring 4 bytes (32 bits or digits) to store as C compiler takes 4 bytes for int.
Now, the second last byte is storing [1111 1111] and the last byte is storing [1111 1110] -> lower byte. The lower byte (rightmost byte) is stored first in little endian machines and the upper byte (leftmost byte) is stored first in big endian machines.
Now when we are accessing *p AFTER p++ (Char *p is a character pointer as declared, remember? So it will access 1 byte at a time, unlike integer pointers which access 4 bytes), we will be getting [1111 1111] or the second last byte. Unlike last time, this is UNSIGNED [%u] thus 2's complement won't be calculated here. The decimal equivalent of 1111 1111 is 255 and so the output should be 255.
HOWEVER: We are getting output 4294967295 which is basically the decimal of [1111.....11] thirty two 1s. WHY?
*******************************************************************************************************************************
WHY IS 2'S BEING CALCULATED FOR CERTAIN NUMBERS AND NOT BEING CALCULATED FOR CERTAIN OTHERS?
The leftmost bit of the first byte indicates if its a negative number (See the chart at the top of the program). Here the rightmost byte is 1111 1110. Or, ->1<-111 1110. The leftmost digit is 1. So, 2's will be done do evaluate the negative number.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 255, output: 0
/*
REASON: 
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 254, output: 0
/*
REASON:
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 1, output: 0
/*
REASON: 
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 128, output: 0
/*
REASON:
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 127, output:0
/*
REASON:
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 129, output: 0
/*
REASON:
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 257, output: 1
/*
REASON:
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: 260, output: 1
/*
REASON: 
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -16, output: 4,294,967,295
/*
REASON: -16 is being stored in 2's complement form. (Like, 011 = +3, then 2's of 011 = 101 = -3. That's how numbers are stored.)
+16 = 0000 0000  0000 0000  0000 0000  0001 0000. 32 bit 2's of +2 = -2 = (1111 1111  1111 1111  1111 1111  1110 1111) + 1 = 1111 1111  1111 1111  1111 1111  1111 0000.
The char pointer is pointing towards the second rightmost bit, 1111 1111. Sign bit here is ->1<-111 1111 or 1 (the rightmost part of the leftmost byte). This bit gets expanded to all the other 15 bits and the output comes as 1111 1111  1111 1111  1111 1111  1111 1111. This is the binary of 4,294,967,295 thus it's getting printed. This is %u so 2's complement won't be applied here.
------------------------------------------------------------------------------------------------------------------------------------------*/
//If i: -, output: 
/*
REASON: 
------------------------------------------------------------------------------------------------------------------------------------------*/
	return 0;
}