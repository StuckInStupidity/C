#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void heads_or_tails(){
	printf("\n**************************************************\n");
	printf("Heads or Tails");
	int money = 500, side = 0, bet = 0, piece = 0;
	srand(time(NULL));
	printf("\n\nYou have %d $", money);
	while (money > 0) {
		do{
			printf("\n\nSide bet ?\n1.Heads\n2.Tails\nChoice : ");
			scanf("%d", &side);
		}while(side!=1 && side!=2);

		do{
			printf("\nHow much on a bet : ");
			scanf("%d", &bet);
		}while(money<bet);

		if(side==1) printf("\nBet %d $ on Heads", bet);
		else printf("\nBet %d $ on Tails", bet);
		piece = (rand() % 2) + 1; // rand() gives a number => rand()%2 gives 0 or 1 => piece will be 1 or 2
		printf("\nThe coin is tossed !");
		printf("\n...");
		printf("\n...");
		if(piece==1) printf("\nIt is Heads !");
		else printf("\nIt is Tails !");
		if (side == piece)
		{
			printf("\n..Congrats !");
			bet *= 2;
			money += bet;
			printf("\nYou now have %d $", money);
		}
		else
		{
			printf("\n..Alright..");
			money -= bet;
			printf("\nYou now have %d $", money);
		}
	}
	printf("\n\nNo more money...");
	printf("\n**************************************************\n");
}