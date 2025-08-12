// Rock, paper, scissor
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Status {CONTINUE, WON_1, WON_2, DRAW};

enum Shape {ROCK, PAPER, SCISSOR};

enum Shape convertIntToShape(int n) {
    return (enum Shape) n;
}

const char * convertShapeToString(enum Shape shape) {
    switch(shape) {
        case ROCK:
            return "Computer chose Rock";
        case PAPER:
            return "Computer chose Paper";
        case SCISSOR:
            return "Computer chose Scissor";
    }
}

// for Robot's shape statistics
int rock_counter = 0;
int paper_counter = 0;
int scissor_counter = 0;
int weight_rock_stat = 33;
int weight_paper_stat = 33;
int weight_scissor_stat = 33;

int calculate_stat() {
    int total_weight_stat = weight_paper_stat + weight_rock_stat + weight_scissor_stat;
    int weight_difference = 0;
    int initialRobotShapeInt = rand()%total_weight_stat;
    int result = 0;
    if(initialRobotShapeInt <= weight_rock_stat) {
        rock_counter+=1;
        weight_difference = weight_rock_stat/2;
        weight_rock_stat -= weight_difference;
        weight_paper_stat += weight_difference/2;
        weight_scissor_stat += weight_difference/2;
        result = 0;
    } else if(initialRobotShapeInt <= weight_paper_stat && initialRobotShapeInt > weight_rock_stat) {
        paper_counter+=1;
        weight_difference = weight_paper_stat/2;
        weight_paper_stat -= weight_difference;
        weight_rock_stat += weight_difference/2;
        weight_scissor_stat += weight_difference/2;
        result = 1;
    } else {
        scissor_counter+=1;
        weight_difference = weight_scissor_stat/2;
        weight_scissor_stat -= weight_difference;
        weight_rock_stat += weight_difference/2;
        weight_paper_stat += weight_difference/2;
        result = 2;
    }
    return result;
}

enum Status gameLogic(enum Shape playerMove, enum Shape robotMove) {
    if(playerMove == robotMove) {
        return DRAW;
    } else if((playerMove == ROCK && robotMove == SCISSOR) || (playerMove == PAPER && robotMove == ROCK) || (playerMove == SCISSOR && robotMove == PAPER)) {
        return WON_1;
    } else {
        return WON_2;
    }
}

_Bool isContinue(int n) {
    return (n==1) ? 1 : 0;
}

int main() {
    srand(time(NULL));
    enum Status status = CONTINUE;

    // main loop of game
    while(status == CONTINUE) {
        // player's Shape initialization
        int playerShapeInt;
        while(1) {
            printf("0-ROCK, 1-Paper, 2-Scissor.\n");
            if(scanf("%d", &playerShapeInt) != 1) {
                printf("Invalid! Input must be a number in range 0-2!\n");
                while(getchar()!='\n');
                continue;
            } else if (playerShapeInt < 0 || playerShapeInt > 2) {
                printf("Invalid! Input must be a number in range 0-2!\n");
                while(getchar()!='\n');
                continue;
            }
            break;
        }
        enum Shape playerShape = convertIntToShape(playerShapeInt);

        // Calculation of robot's potential shape statistics
        int robotShapeInt = calculate_stat();

        enum Shape robotShape = convertIntToShape(robotShapeInt);
        printf("%s\n", convertShapeToString(robotShape));
        int isContinue = 0;
        switch(gameLogic(playerShape, robotShape)) {
            case DRAW:
                printf("DRAW! \n");
                break;
            case WON_1:
                printf("Player won! \n");
                break;
            case WON_2:
                printf("Robot won! \n");
                break;
        }

        printf("Continue the game? 1-Continue,0-No.\n");
        scanf("%d", &isContinue);
        if(!isContinue) {
            break;
        }
    }

    printf("GAME OVER!\n");

    return 0;
}