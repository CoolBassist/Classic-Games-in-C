#include <stdio.h>
#include <stdlib.h>

#define yellowcol "\e[0;33m"
#define redcol "\e[0;34m"
#define resetcol "\e[0m"

#define fullcircle "\U000025cf"
#define emptycircle "\U000025ef"

enum state {empty, red, yellow};

void draw_board(enum state[6][7]);
int game_over(enum state[6][7]);

int main(){
    enum state board[6][7];
    int column_height[7];
    int player_turn = 0;
    int player_choice;
    char c;

    //initialising the board, and height arrays.

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            board[i][j] = empty;
            column_height[j] = 0;
        }
    }

    // main game loop.
    while(1){
        system("clear");
        printf("\n");
        draw_board(board);
        do{
            printf("Player %d> ", player_turn+1);
            while(!scanf("%d", &player_choice)){
                printf("Please enter a number between 1 and 7 for a column that isnt empty: ");
                while(c=getchar(), c != EOF && c != '\n'){} // flushing input
            }
        }while(column_height[player_choice] == 6 || player_choice > 7 || player_choice < 1);

        board[5-column_height[player_choice]][player_choice-1] = player_turn? red : yellow;
        column_height[player_choice]++;

        if(game_over(board)){
            break;
        }

        player_turn = !player_turn;
    }

    system("clear");
    printf("\n");

    draw_board(board);

    printf("Player %d wins!\n", player_turn+1);

    return 0;
}

void draw_board(enum state board[6][7]){
    for(int i = 0; i < 6; i++){
        printf("│");
        for(int j = 0; j < 7; j++){
            switch(board[i][j]){
                case red: printf("%s%s%s",redcol, fullcircle, resetcol); break;
                case yellow: printf("%s%s%s", yellowcol, fullcircle, resetcol); break;
                case empty: printf("%s", emptycircle); break;
            }
        }
        printf("│\n");
    }
    printf("╰───────╯\n");
    printf(" 1234567\n");
}

int game_over(enum state board[6][7]){
    int won = 0;

    // check rows
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j] == empty){
                continue;
            }
            won = won || (board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] == board[i][j+3]);
        }
    }

    // check columns
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 7; j++){
            if(board[i][j] == empty){
                continue;
            }
            won = won || (board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j] && board[i][j] == board[i+3][j]);
        }
    }

    // check left to right diagonals
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j] == empty){
                continue;
            }

            won = won || (board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2] && board[i][j] == board[i+3][j+3]);
        }
    }

    // check right to left diagonals
    for(int i = 0; i < 3; i++){
        for(int j = 3; j < 7; j++){
            if(board[i][j] == empty){
                continue;
            }

            won = won || (board[i][j] == board[i+1][j-1] && board[i][j] == board[i+2][j-2] && board[i][j] == board[i+3][j-3]);
        }
    }


    return won;
}