#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>

void mystery1(){
	printf("\n**************************************************\n");
	printf("Guess the word");

	char *list[] = {"computer", "mountain", "language", "keyboard", "airplane",
	"sunshine", "elephant", "building", "umbrella", "dinosaur",
	"notebook", "triangle", "football", "backpack", "sandwich",
	"calendar", "hospital", "internet", "magazine", "painting",
	"treasure", "vacation", "wildlife", "chocolate", "adventure",
	"astronomy", "butterfly", "crocodile", "diamond", "electric",
	"festival", "galaxy", "harmony", "island", "jungle",
	"kingdom", "library", "machine", "necklace", "ocean",
	"penguin", "rainbow", "science", "tornado", "universe",
	"volcano", "weather", "yesterday", "zookeeper", "qubit"};

	int cnt = sizeof(list) / sizeof(list[0]);
	srand(time(NULL));
	int index = rand() % cnt;
	char *secret = list[index];
	int length = strlen(secret);
	int errors = 7; int won=0;

	char shuffle[10] = {'\0'}; strcpy(shuffle, secret);
	for(int i = length-1; i > 0; i--){
		int j = rand() % (i+1);
		char tmp = shuffle[i];
		shuffle[i]=shuffle[j];
		shuffle[j]=tmp;
	}

	while (errors>0 && !won){
		
		printf("\n\n-----Wrong answers allowed : %d-----", errors);
		printf("\nShuffled word: %s", shuffle);
		printf("\nYour guess: ");
		char guess[10]; scanf("%9s", guess); //protection char limit
		if(strcmp(guess, secret)==0) won=1;
		else {errors--; printf("Nope...\n");}
	}
	if (won) printf("\n\nYou won ! It was : %s", secret);
	else printf("\n\nYou lost ! It was : %s", secret);
	printf("\n**************************************************\n");
}