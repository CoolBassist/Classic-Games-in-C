#include <stdio.h>
#include <stdlib.h>

void draw_board(int[]);
int has_won(int[], int);

int main(){
    int seeds_per_pit;
    system("clear");
    printf("Please enter how many seeds you would per pit: ");
    while(!scanf("%d", &seeds_per_pit)){
        printf("Please enter a number. We recommend between 3 and 6\n");
    }

    int pits[14];

    for(int i = 0; i < 14; i++){
        pits[i] = ((i+1)%7) == 0? 0 : seeds_per_pit; // initialising all pits to what the user specified, except for the stores.
    }

    int player_turn = 0;
    int player_choice;
    int current_pit;
    int num_of_seeds;
    system("clear");
    printf("\n");

    while(1){
        draw_board(pits);
        do{
            do{
                printf("Player %d> ", player_turn + 1);
                while(!scanf("%d", &player_choice)){
                    printf("Please enter a number between 0 and 5, and a pit that isnt empty.\n");
                }
            }while(player_choice > 5 || player_choice < 0);
            current_pit = player_turn? (7+player_choice) : (5-player_choice);
        }while(pits[current_pit] == 0);

        num_of_seeds = pits[current_pit];

        pits[current_pit] = 0;
        
        for(int i = 0; i < num_of_seeds;){
            if((current_pit == 6 && player_turn) || (current_pit == 13 && !player_turn)){
                continue;
            }

            pits[++current_pit%14]++;
            i++;
        }

        system("clear");

        if(current_pit == 6 || current_pit == 13){
            printf("Player %d gets another turn!\n", player_turn + 1);
            continue;
        }else if(pits[current_pit] == 1){
            int steal_pit = 12 - current_pit;
            if((steal_pit > 6 && steal_pit < 13 && !player_turn) || (steal_pit >= 0 && steal_pit < 6 && player_turn)){
                if(pits[steal_pit] != 0){
                    printf("Player %d steals!\n", player_turn + 1);
                    pits[player_turn? 13 : 6] += pits[steal_pit] + pits[current_pit];
                    pits[steal_pit] = 0;
                    pits[current_pit] = 0;
                }       
            }
        }else{
            printf("\n");
        }

        if(has_won(pits, seeds_per_pit)){
            break;
        }

        player_turn = !player_turn;
    }

    draw_board(pits);

    printf("Player %d wins!\n", (pits[6] > pits[13]? 1 : 2));

    return 0;
}

void draw_board(int pits[]){
    printf("╭──┬──┬──┬──┬──┬──┬──┬──╮\n│  ");

    for(int i = 5; i >= 0; i--){
        printf("│%2d", pits[i]); // printing top row
    }

    printf("│  │\n│%2d├──┼──┼──┼──┼──┼──┤%2d│\n│  ", pits[6], pits[13]); // printing stores

    for(int i = 7; i < 13; i++){
        printf("│%2d", pits[i]); // printing bottom row
    }

    printf("│  │\n╰──┴──┴──┴──┴──┴──┴──┴──╯\n   ");
    
    for(int i = 0; i < 6; i++){
        printf("┆%2d", i);
    }

    printf("┆\n");
}

int has_won(int pits[], int seeds_per_pit){
    if((pits[6] > seeds_per_pit*6) || (pits[13] > seeds_per_pit*6)){
        printf("win by more than half of the seeds\n");
        return 1;
    }

    int sum = 0;

    for(int i = 0; i < 6; i++){
        sum += pits[i];
    }

    if(sum == 0){
        for(int i = 7; i < 13; i++){
            pits[13] += pits[i];
            pits[i] = 0;
        }
        printf("Win by player 1 having no seeds on their side.\n");
        return 1;
    }

    sum = 0;

    for(int i = 7; i < 13; i++){
        sum += pits[i];
    }

    if(sum == 0){
        for(int i = 0; i < 6; i++){
            pits[6] += pits[i];
            pits[i] = 0;
        }
        printf("Win by player 2 having no seeds on their side.\n");
        return 1;
    }

    return 0;
}