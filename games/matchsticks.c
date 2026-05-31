#include<stdio.h>
#include<stdlib.h>

void matchsticks(){
    printf("\n**************************************************\n");
    printf("Matchsticks\n\n");
    int total = 12;
    int player, computer = 0;
    do
    {
	for(int i=0; i < 4; i++){
		for(int nb = 0; nb < total; nb++) printf("|  ");
		printf("\n");
	}

	do{
        	printf("\nHow many to get rid of ? 1, 2 ou 3 :  ");
        	scanf("%d", &player);
	}while(player > total || (player!=1 && player!=2 && player!=3));

	total -= player;
        printf("\n%d matchstick(s) remaining !\n\n", total);

        if (total == 0)
        {
            printf("\n..Game Over...");
	    printf("\n**************************************************\n");
	    break;
        }

	for(int i=0; i < 4; i++){
		for(int nb = 0; nb < total; nb++) printf("|  ");
		printf("\n");
	}

        switch (total){
        case 1:
            computer = 1; //loosing anyway
            break;
        case 2:
            computer = 1; //winning anyway
            break;
        case 3:
            computer = 2; //winning anyway
            break;
        case 4:
            computer = 3; //winning anyway
            break;
        case 5:
            computer = 3; //loosing anyway
            break;
        case 6:
            computer = 1; //winning anyway
            break;
        case 7:
            computer = 2; //winning anyway
            break;
        case 8:
            computer = 3; //winning anyway
            break;
        case 9:
            computer = 1; //loosing anyway
            break;
        case 10:
            computer = 1; //winning anyway
            break;
        case 11:
            computer = 2; //winning anyway
            break;
        }
	//this game's trick is just that the first one who starts, takes 3 and follow rationally will always be winning

        printf("\nThe computer takes %d matchstick(s) !", computer);
	total -= computer;

        printf("\n%d matchstick(s) remaining !\n\n", total);

        if (total == 0)
        {
            printf("\n..Yay !");
	    printf("\n**************************************************\n");
        }

    }while (total > 0);
}