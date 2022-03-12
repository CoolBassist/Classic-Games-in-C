#include <stdio.h>
#include <stdlib.h>

enum STATE {empty, cross, naught};

void draw_board(enum STATE[3][3]);
int has_won(enum STATE[3][3]);

int main(){
	enum STATE board[3][3];

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			board[i][j] = empty;
		}
	}

	int player_turn = 0;
	int x, y;

	while(1){ //main game loop
		draw_board(board);

		//take input
		while(1){
			printf("Player %d, please enter coord for move: ", player_turn+1);
			scanf("%d%d", &x, &y);
			if(x < 0 || x > 3 || y < 0 || y > 3){
				printf("Please enter a valid coord.\n");
			}else if(board[y][x] != empty){
				printf("Space already occupied!\n");
			}else{
				break; // input is valid and space is empty.
			}
		}

		board[y][x] = player_turn ? naught : cross;

		if(has_won(board)){
			break;
		}
		player_turn = !player_turn;
	}

	draw_board(board);

	printf("Player %d won!", player_turn + 1);

	return 0;
}

void draw_board(enum STATE board[3][3]){
	printf("╔═══╤═══╤═══╗\n");
	for(int i = 0; i < 3; i++){
		printf("║");
		for(int j = 0; j < 3; j++){
			switch(board[i][j]){
				case empty: printf("   "); break;
				case cross: printf(" X "); break;
				case naught: printf(" O "); break;
			}
			if(j == 2){
				printf("║");
			}else{
				printf("│");
			}
		}
		if(i == 2){
			printf("\n╚═══╧═══╧═══╝\n");
		}else{
			printf("\n╟───┼───┼───╢\n");
		}
	}
}

int has_won(enum STATE board[3][3]){
	int won = 0;

	for(int i = 0; i < 3; i++){ // checking columns and rows.
		won = won || (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != empty);
		won = won || (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != empty);
	}

	won = won || (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != empty); // checking diagonals 
	won = won || (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != empty);

	return won;
}
