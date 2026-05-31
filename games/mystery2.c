#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mystery2(){
	printf("\n**************************************************\n");
	printf("You guess computer's number (from 1 to 1000)");
	srand(time(NULL));
	int secret = rand()%1000 +1;
	int trials = 11;
	int guess;
	for(int i = 1; i <= trials; i++){
		printf("\n\n-----Trial %d/11-----", i);
		printf("\nYour guess : ");
		scanf("%d", &guess);
		if(guess==secret) break;
		else if(guess < secret) printf("\nBigger...");
		else printf("\nSmaller...");
	}
	if(guess==secret) printf("\n\nYou won !");
	else printf("\n\nYou lost !");
	printf("\n**************************************************\n");
}