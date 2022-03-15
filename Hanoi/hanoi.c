#include <stdio.h>
#include <stdlib.h>

void draw_pegs(int[7][3]);
int game_over(int, int);
void draw_disk(int, int);

int main(){
    int board[7][3];
    int peg_heights[3] = {0, 0, 0};
    int number_of_disks;

    while(1){
        printf("Please enter how many disks you would like: ");
        if(!scanf("%d", &number_of_disks)){
            printf("Please enter a number.\n");
        }else if(number_of_disks > 6 || number_of_disks < 1){
            printf("Please enter a number between 1 and 6\n");
        }else{
            break;
        }
    }

    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = 0;
        }
    }

    for(int i = 0; i < number_of_disks; i++){
        board[i][0] = number_of_disks - i;
    }

    peg_heights[0] = number_of_disks;

    int src_player_move;
    int dst_player_move;

    int number_of_moves = 0;

    while(!game_over(peg_heights[2], number_of_disks)){
        system("clear");
        draw_pegs(board);

        while(1){
            while(1){
                printf("Please enter the source peg: ");
                if(!scanf("%d", &src_player_move)){
                    printf("Please enter a number.\n");
                }else if(src_player_move > 3 || src_player_move < 1){
                    printf("Please enter a number in the range 1-3.\n");
                }else{
                    break;
                }
            }
            while(1){
                printf("Please enter the destination peg: ");
                if(!scanf("%d", &dst_player_move)){
                    printf("Please enter a number.\n");
                }else if(dst_player_move > 3 || dst_player_move < 1){
                    printf("Please enter a number in the range 1-3.\n");
                }else{
                    break;
                }
            }

            if(peg_heights[dst_player_move-1] != 0 && (board[peg_heights[dst_player_move-1]-1][dst_player_move-1] < board[peg_heights[src_player_move-1]-1][src_player_move-1])){
                printf("The destination peg must be larger than the source peg.\n");
            }else if(dst_player_move == src_player_move){
                printf("You cannot move a disk to itself.\n");
            }else{
                break;
            }
        }

        board[peg_heights[dst_player_move-1]][dst_player_move-1] = board[peg_heights[src_player_move-1]-1][src_player_move-1];
        board[peg_heights[src_player_move-1]-1][src_player_move-1] = 0;


        peg_heights[src_player_move-1]--;
        peg_heights[dst_player_move-1]++;    
        number_of_moves++;    
    }

    system("clear");

    draw_pegs(board);
    printf("You won in %d moves!", number_of_moves);

    return 0; 
}

void draw_pegs(int board[7][3]){
    printf("        ╭╮                ╭╮                ╭╮\n");
    for(int i = 6; i >= 0; i--){
        for(int j = 0; j < 3; j++){
            draw_disk(board[i][j], board[i+1][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < 3; i++){
        if(board[0][i] == 0){
            printf("════════╧╧════════");
        }else if(board[0][i] == 1){
            printf("═══════╧══╧═══════");
        }else if(board[0][i] == 2){
            printf("══════╧════╧══════");
        }else if(board[0][i] == 3){
            printf("═════╧══════╧═════");
        }else if(board[0][i] == 4){
            printf("════╧════════╧════");
        }else if(board[0][i] == 5){
            printf("═══╧══════════╧═══");
        }else if(board[0][i] == 6){
            printf("══╧════════════╧══");
        }
    }

    printf("\n");
}

int game_over(int height, int number_of_disks){
    return height == number_of_disks;
}

void draw_disk(int disk, int disk_above){
    if(disk == 0){
        printf("        ││        ");
    }else if(disk == 1){
        printf("       ╭┴┴╮       ");
    }else if(disk == 2){
        if(disk_above == 1){
            printf("      ╭┴──┴╮      ");
        }else{
            printf("      ╭─┴┴─╮      ");
        }
    }else if(disk == 3){
        if(disk_above == 1){
            printf("     ╭─┴──┴─╮     ");
        }else if(disk_above == 2){
            printf("     ╭┴────┴╮     "); 
        }else{
            printf("     ╭──┴┴──╮     "); 
        }
    }else if(disk == 4){
        if(disk_above == 1){
            printf("    ╭──┴──┴──╮    ");
        }else if(disk_above == 2){
            printf("    ╭─┴────┴─╮    "); 
        }else if(disk_above == 3){
            printf("    ╭┴──────┴╮    "); 
        }else{
            printf("    ╭───┴┴───╮    "); 
        }
    }else if(disk == 5){
        if(disk_above == 1){
            printf("   ╭───┴──┴───╮   ");
        }else if(disk_above == 2){
            printf("   ╭──┴────┴──╮   "); 
        }else if(disk_above == 3){
            printf("   ╭─┴─────┴─╮   "); 
        }else if(disk_above == 4){
            printf("   ╭┴────────┴╮   "); 
        }else{
            printf("   ╭────┴┴────╮   "); 
        }
    }else if(disk == 6){
        if(disk_above == 1){
            printf("  ╭────┴──┴────╮  ");
        }else if(disk_above == 2){
            printf("  ╭───┴────┴───╮  "); 
        }else if(disk_above == 3){
            printf("  ╭──┴──────┴──╮  "); 
        }else if(disk_above == 4){
            printf("  ╭─┴────────┴─   "); 
        }else if(disk_above == 5){
            printf("  ╭┴──────────┴╮  "); 
        }else{
            printf("  ╭─────┴┴─────╮  "); 
        }
    }
}