// Rock, paper, scissors

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Move {ROCK, PAPER, SCISSOR};

enum Status {CONTINUE, WON_1, WON_2, DRAW};

enum Move convertIntToMove(int n) {
    return (enum Move) n;
}

const char * convertMoveToString(enum Move move) {
    switch(move) {
        case ROCK:
            return "Computer chose Rock";
        case PAPER:
            return "Computer chose Paper";
        case SCISSOR:
            return "Computer chose Scissor";
    }
}

enum Status gameLogic(enum Move playerMove, enum Move robotMove) {
    if(playerMove == robotMove) {
        return DRAW;
    } else if((playerMove == ROCK && robotMove == SCISSOR) || (playerMove == PAPER && robotMove == ROCK) || (playerMove == SCISSOR && robotMove == PAPER)) {
        return WON_1;
    } else {
        return WON_2;
    }
}

int main() {
    srand(time(NULL));

    enum Status status = CONTINUE;

    while(status == CONTINUE) {
        int playerMoveInt = -1;
        while(1) {
            printf("Choose! 0 - Rock, 1 - Paper, 2 - Scissor. \n");
            if(scanf("%d", &playerMoveInt) != 1) {
                printf("Ivalud input! Input must be a number!\n");
                while(getchar() != '\n');
                continue;
            } else if(playerMoveInt < 0 || playerMoveInt > 2) {
                printf("Input number must be in range 0-2.\n");
                while(getchar() != '\n');
                continue;
            }
            break;
        }
        enum Move playerMove = convertIntToMove(playerMoveInt);
        enum Move robotMove = convertIntToMove(rand() % 3);
        printf("%s\n", convertMoveToString(robotMove));
        switch(gameLogic(playerMove, robotMove)) {
            case DRAW:
                printf("DRAW! Play again! \n");
                break;
            case WON_1:
                printf("Player won! \n");
                status = WON_1;
                break;
            case WON_2:
                printf("Robot won! \n");
                status = WON_2;
                break;
        }
    }

    printf("GAME OVER!");


    return 0;
}