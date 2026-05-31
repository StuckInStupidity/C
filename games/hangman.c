#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>

void hangman(){
	printf("\n**************************************************\n");
	printf("Hangman");

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
	int unveiled[length];
	memset(unveiled, 0, sizeof(int) * length);
	int errors = 7; int won=0;

	while (errors>0 && !won){
		
		printf("\n\n-----Wrong answers allowed : %d-----", errors);
		printf("\nWhat is the word (lowercases only) : ");

		for (int i = 0; i < length; i++) {
			if (unveiled[i]) printf("%c", secret[i]);
			else printf("*");
		}

		char letter; printf("\nLetter : "); scanf(" %c", &letter); //multiple letters will do multiple changes, no pb
		int found=0; for(int i=0; i < length; i++) if(secret[i]==letter) {unveiled[i]=1; found=1;}
		if(!found) {errors--; printf("Not found...\n");}
		else {won=1; for(int i=0; i < length; i++) if(!unveiled[i]) won=0;}
	}
	if (won) printf("\n\nYou won ! It was : %s", secret);
	else printf("\n\nYou lost ! It was : %s", secret);
	printf("\n**************************************************\n");
}