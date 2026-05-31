#include <stdio.h>
#include <stdlib.h>

void mystery3(){
	printf("\n**************************************************\n");
	printf("Make the computer guess your number (from 1 to 1000)\n");
	printf("Enter +, - or =\n");
	int min=1, max=1000, mid; char c = ' ';
	while(c!='=' && min < max){
		mid = (max+min)/2;
		printf("\nIs it %d ? ", mid);
		scanf(" %c", &c); //multiple + or - will change the value multiple times, no pb
		//important ! => for char scanf put that whitespace before %c to tell him to ignore the whitespace before the actual input
		//to avoid double print or bugs
		if(c=='+') min = mid+1;
		else if(c=='-') max = mid-1;
	}
	if(c=='=') printf("\n\nYay !");
	else printf("\n\nStop messing with me !");
	printf("\n**************************************************\n");

}