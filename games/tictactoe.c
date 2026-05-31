#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_grid(char grid[3][3]){
    printf("\n\n   1   2   3 \n");
	printf(" |---|---|---|\n");
	printf("A| %c | %c | %c |\n", grid[0][0], grid[0][1], grid[0][2]);
	printf(" |---|---|---|\n");
	printf("B| %c | %c | %c |\n", grid[1][0], grid[1][1], grid[1][2]);
	printf(" |---|---|---|\n");
	printf("C| %c | %c | %c |\n", grid[2][0], grid[2][1], grid[2][2]);
	printf(" |---|---|---|\n");
}

void tic_tac_toe(){
	printf("\n**************************************************\n");
	printf("Tic Tac Toe");
	//char grid[3][3] = {' '}; only first = ' ', the rest equal '\0'
	char grid[3][3];
	memset(grid, ' ', sizeof(grid)*sizeof(char)); 
	//this fills each byte with ' ', so safe for char since there is only one byte
	//but for int : memset(arr, 1, sizeof(arr)*sizeof(int)); => gives 0x01010101  (16843009 in decimal) not 1, only 0 is safe then
	int turn = 1, not_over=1, not_ok = 1, s=0;
	char c1[3]; char c2[3];

	do{
        print_grid(grid);

		if(turn==1){

			turn=2;
			do{
				printf("\nPlayer 1, enter the coordinates of the case : ");
				scanf("%s", c1);
				if(strlen(c1)!=2) continue;
				not_ok = (c1[0]!='A' && c1[0]!='B' && c1[0]!='C') || (c1[1]!='1' && c1[1]!='2' && c1[1]!='3');
				if(not_ok) continue;
				not_ok = (grid[c1[0]-'A'][c1[1]-'1']!=' ');
			}while(not_ok);
			
			grid[c1[0]-'A'][c1[1]-'1'] = 'X'; 
			s++;

			if(
			(grid[0][0]=='X' && grid[0][1] == 'X' && grid[0][2] == 'X') ||
			(grid[1][0]=='X' && grid[1][1] == 'X' && grid[1][2] == 'X') ||
			(grid[2][0]=='X' && grid[2][1] == 'X' && grid[2][2] == 'X') ||

			(grid[0][0]=='X' && grid[1][0] == 'X' && grid[2][0] == 'X') ||
			(grid[0][1]=='X' && grid[1][1] == 'X' && grid[2][1] == 'X') ||
			(grid[0][2]=='X' && grid[1][2] == 'X' && grid[2][2] == 'X') ||

			(grid[0][0]=='X' && grid[1][1] == 'X' && grid[2][2] == 'X') ||
			(grid[0][2]=='X' && grid[1][1] == 'X' && grid[2][0] == 'X')
			) {print_grid(grid); printf("\n\nPlayer 1 has won !"); not_over=0;}
		}
		else{

			turn=1;
			do{
				printf("\nPlayer 2, enter the coordinates of the case : ");
				scanf("%s", c2);
				if(strlen(c2)!=2) continue;
				not_ok = (c2[0]!='A' && c2[0]!='B' && c2[0]!='C') || (c2[1]!='1' && c2[1]!='2' && c2[1]!='3');
				if(not_ok) continue;
				not_ok = (grid[c2[0]-'A'][c2[1]-'1']!=' ');
			}while(not_ok);

			grid[c2[0]-'A'][c2[1]-'1'] = 'O'; 
			s++;

			if(
			(grid[0][0]=='O' && grid[0][1] == 'O' && grid[0][2] == 'O') ||
			(grid[1][0]=='O' && grid[1][1] == 'O' && grid[1][2] == 'O') ||
			(grid[2][0]=='O' && grid[2][1] == 'O' && grid[2][2] == 'O') ||

			(grid[0][0]=='O' && grid[1][0] == 'O' && grid[2][0] == 'O') ||
			(grid[0][1]=='O' && grid[1][1] == 'O' && grid[2][1] == 'O') ||
			(grid[0][2]=='O' && grid[1][2] == 'O' && grid[2][2] == 'O') ||

			(grid[0][0]=='O' && grid[1][1] == 'O' && grid[2][2] == 'O') ||
			(grid[0][2]=='O' && grid[1][1] == 'O' && grid[2][0] == 'O')
			) {print_grid(grid); printf("\n\nPlayer 2 has won !"); not_over=0;}
		}
		
		if(not_over && s >= 9) {printf("\n\nDraw !"); not_over = 0;}
		
	}while(not_over);
	printf("\n**************************************************\n");
}