#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void chifoumi(){
	printf("\n**************************************************\n");
	printf("Rock Paper Scissors");
	int player, computer, p=0, c=0;
	srand(time(NULL));

	for(int i = 1; i <= 3; i++){
		printf("\n\n---Round %d/3 %d:%d---", i, p, c);
		do{
			printf("\n\n1.Rock\n2.Paper\n3.Scissors\nChoice : ");
			scanf("%d", &player);
		}while(player!=1 && player!=2 && player!=3);

		computer = (rand() % 3) + 1;
		if(computer==1) printf("\nComputer chose.. Rock !");
		else if(computer==2) printf("\nComputer chose.. Paper !");
		else printf("\nComputer chose.. Scissors !");
		
		if(player==computer) {printf("\nDraw !"); i--;}
		else if(player==1 && computer==3 || player==2 && computer==1 || player==3 && computer==2) {printf("\nYou won !"); p++;}
		else {printf("\nYou lost !"); c++;}
	}
	printf("\n\n----------");
	if(p>c){
		printf("\nYou ultimately won !");
		printf("\n**************************************************\n");
	}
	else{
		printf("\nYou ultimately lost !");
		printf("\n**************************************************\n");
	}
	
}
