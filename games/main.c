#include <stdio.h>
#include <string.h>
#include "games.h"

void help() {
	printf("\n**************************************************\n");
	printf("Commandes disponibles :\n");
	printf("  HeadsTails       - play heads or tails\n");
	printf("  TicTacToe        - play tic tac toe\n");
	printf("  matchsticks      - play matchsticks\n");
	printf("  hangman          - play hangman\n");
	printf("  mystery1         - guess the word\n");
	printf("  mystery2         - you guess computer's number\n");
	printf("  mystery3         - computer guesses your number\n");
	printf("  chifoumi         - play rock paper scissors\n");
	printf("  help             - print help\n");
	printf("  quit             - quit game menu\n");
	printf("**************************************************\n");
}

int main(){
	printf("*********GAMES !*********\n");
	char choice[15];
	do{
		printf("\n> ");
		scanf("%14s", choice); //protection limit to 14 char which is the longest cmd here
		if (strcmp(choice, "quit") == 0) printf("\n*********Bye !*********\n");
		else if (strcmp(choice, "chifoumi") == 0) chifoumi();
		else if (strcmp(choice, "mystery1") == 0) mystery1();
		else if (strcmp(choice, "mystery2") == 0) mystery2();
		else if (strcmp(choice, "mystery3") == 0) mystery3();
		else if (strcmp(choice, "hangman") == 0) hangman();
		else if (strcmp(choice, "matchsticks") == 0) matchsticks();
		else if (strcmp(choice, "TicTacToe") == 0) tic_tac_toe();
		else if (strcmp(choice, "HeadsTails") == 0) heads_or_tails();
		else help();
	
	}while(strcmp(choice, "quit")!=0);
	//printf("\nCe fichier a ete compiler le %s a %s\n", __DATE__, __TIME__);
	return 0;
}