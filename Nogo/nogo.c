#include <stdio.h>
#include <stdlib.h>

#define height 5
#define width 5

enum state {empty, cross, naught};

void draw_board(enum state[height][width]);
int get_liberties(enum state[height][width], int, int, int state[height][width], int);
int has_won(enum state[height][width]);
void human_turn(enum state[height][width], int);
void computer_turn(enum state[height][width], int);

int main(){
	system("clear");
	enum state board[height][width];
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			board[i][j] = empty;
		}
	}

	//setting up game variables
	int players[2];
	int player_turn = 0;

	char player_choice;

	for(int i = 0; i < 2; i++){
		do{
			printf("Do you want player %d to be (h)uman or a (c)omputer? ", i+1);
			while((player_choice = getchar()) == '\n' || player_choice == EOF){} //get char from user, and flush input buffer
		}while(player_choice != 'h' && player_choice != 'c');

		players[i] = player_choice;
	}

	while(1){
		draw_board(board);

		if(players[player_turn] == 'h'){
			human_turn(board, player_turn);
		}else{
			computer_turn(board, player_turn);
		}

		if(has_won(board)){
			break;
		}

		player_turn = 1 - player_turn;
	}

	draw_board(board);

	printf("Player %c won!\n", player_turn == 0? 'x' : 'o');

	return 0;
}

void draw_board(enum state board[height][width]){
	printf("┌nogo");
	for(int i = 0; i < width-2; i++){
		printf("───┬");
	}
	printf("───┐\n");
	for(int i = 0; i < height; i++){
		printf("│");
		for(int j = 0; j < width; j++){
			switch(board[i][j]){
				case empty: printf("   │"); break;
				case cross: printf(" x │"); break;
				case naught: printf(" o │"); break;
			}
		}

		if(i == height-1){
			printf("\n└───");
			for(int k = 0; k < width-1; k++){
				printf("┴───");
			}
			printf("┘\n");
		}else{
			printf("\n├───");
			for(int k = 0; k < width-1; k++){
				printf("┼───");
			}
			printf("┤\n");
		}
	}
}

void human_turn(enum state board[height][width], int player_turn){
	int x, y;

	do{
		do{
			printf("Player %c> ", player_turn == 0 ? 'x' : 'o');
			scanf("%d%d", &x, &y);
		}while(x > width || 0 > x || y > height ||0 > y);
	}while(board[y][x] != empty);

	board[y][x] = player_turn == 0? cross : naught;
}

void computer_turn(enum state board[height][width], int player_turn){
	int i_r = player_turn == 0? 2 : 1;
	int i_c = player_turn == 0? 10 : 4;
	int f = player_turn == 0? 17 : 29;
	int m = 0;

	//initial setup
	int r = i_r;
	int c = i_c;
	int b = i_r * width + i_c;

	int x, y;
	y = r % height;
	x = c % width;

	while(board[y][x] != empty){
		if(m % 5 == 0){
			int n = (b + (m/5)*f) % 1000003;
			r = n/width;
			c = n % width;
		}else{
			switch(m % 5){
				case 1: r += 1; c += 1; break;
				case 2: r += 2; c += 1; break;
				case 3: r += 1; c += 0; break;
				case 4: r += 0; c += 1; break;
			}
		}
		++m;

		y = r % height;
		x = c % width;
	}

	board[y][x] = player_turn == 0? cross: naught;

	printf("player %c: %d %d\n", player_turn == 0? 'x': 'o', x, y);
}

int has_won(enum state board[height][width]){

	int discovered[height][width];

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(get_liberties(board, j, i, discovered, 1) == 0){
				printf("%d %d has no liberties!\n", j, i);
				return 1;
			}
		}
	}

	return 0;
}

int get_liberties(enum state board[height][width], int x, int y, int discovered[height][width], int base){
	int liberties = 0;

	if(base == 1){
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				discovered[i][j] = 0;
			}
		}
	}

	discovered[y][x] = 1;	

	if(board[y][x] != empty){
		if(x - 1 > 0){
			if(board[y][x-1] == empty){
				liberties++;
			}else if(board[y][x-1] == board[y][x] && !discovered[y][x-1]){
				liberties += get_liberties(board, x-1, y, discovered, 0);
			}
		}

		if(x + 1 < width){
			if(board[y][x+1] == empty){
				liberties++;
			}else if(board[y][x+1] == board[y][x] && !discovered[y][x+1]){
				liberties += get_liberties(board, x+1, y, discovered, 0);
			}
		}

		if(y - 1 > 0){
			if(board[y-1][x] == empty){
				liberties++;
			}else if(board[y-1][x] == board[y][x] && !discovered[y-1][x]){
				liberties += get_liberties(board, x, y-1, discovered, 0);
			}
		}

		if(y + 1 < height){
			if(board[y+1][x] == empty){
				liberties++;
			}else if(board[y+1][x] == board[y][x] && !discovered[y+1][x]){
				liberties += get_liberties(board, x, y+1, discovered, 0);
			}
		}

		return liberties;
	}

	return -1;
}	
