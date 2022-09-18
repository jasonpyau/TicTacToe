#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int board[9] = {0,0,0,0,0,0,0,0,0};
void gameLoop();
void welcomeScreen();
void clearScreen();
void drawScreen();
int askInput();
int checkInput(int,int);
int gameMoves = 0;
void delay(double);
void updateScreen(int, int);
int checkBoard(int);
void computerMove(int);
int boardChoicePoint(int, int);
int playerWins = 0;
int computerWins = 0;
int draws = 0;

// Main function 
int main() {
    welcomeScreen();
    gameLoop();
}

void gameLoop() {
    time_t t;
    srand((unsigned) time(&t));
    int winner = 0;
    while(1) {
        drawScreen();
        while(gameMoves<9) {
            if (gameMoves != 0 || rand()%2==0) {
                int boardNum = askInput();
                updateScreen(1,boardNum);
                if (checkBoard(1) != 0) {
                    winner = 1;
                    break;
                }
            }
            computerMove(gameMoves);
            if (checkBoard(2) != 0) {
                winner = 2;
                break;
            }
        }
        clearScreen();
        drawScreen();
        if (winner == 1) {
            printf("\n  Player has won the match.\n");
            playerWins++;
        }
        else if (winner == 2) {
            printf("\n  Computer has won the match.\n");
            computerWins++;
        }
        else {
            printf("\n  Draw, no one won the match.\n");
            draws++;
        }
        gameMoves = 0;
        winner = 0;
        for (int k = 0; k<9; k++) {
            board[k]=0;
        }
        printf("\n  Press <enter> to continue.\n\n");
        clearScreen();
    }
}

// Outputs welcome and instruction
void welcomeScreen() {
    system("cls");
    printf("\n   Tic Tac Toe\n\n  Welcome to Tic Tac Toe! The objective of this game is to get three in\n");
    printf("  a row (horizontally, diagonally, or vertically) against the Computer.\n");
    printf("  The Player's symbol is X, while the Computer's symbol is O.\n");
    printf("\n  Press <enter> to continue.");
    clearScreen();
}

//Clears screen
void clearScreen() {
    char enter; 
    scanf("%c", &enter);
    system("cls");
}

//Draws and updates screen after each move
void drawScreen() {
    char item = ' ';
    int i = 0;
    printf("\n   Tic Tac Toe\n");
    printf("\n  Player Wins: %d", playerWins);
    printf("\n  Draws: %d", draws);
    printf("\n  Computer Wins: %d\n\n  -------------\n  ", computerWins);
    for (int c = 0; c < 3; c++) {
        for (int r = 0; r < 3; r++) {
            if(board[i]==1)
                item = 'X';
            else if(board[i]==2)
                item = 'O';
            else
                item = ' ';
            printf("| %c ", item);
            i++;
        }
        printf("|\n  ");
    }
    printf("-------------\n");
}

int askInput() {
    int num = 0;
    num = (checkInput(1, num)-1)*3;
    num += checkInput(2, num);
    num += -1;
    return num;
}

int checkInput(int type, int num) {
    int input=0;
    while(1) {
        if (type==1)
            printf("\n  Input a row [1,2,3]\n");
        else
            printf("\n  Input a column [1,2,3]\n");
        printf("  Input: ");
        while (scanf("%d", &input)==1) {
            if ((input==1)||(input==2)||(input==3)) {
                int count = 0;
                for(int i = 0; i<3;i++) {
                    if (!(board[(input-1)*3+i]==0)&&type==1)
                        count++;
                }
                if (count==3) {
                    break;
                }
                if((!(board[num+input-1]==0))&&type==2) {
                    break;
                }
                if(type==2)
                    gameMoves++;
                return input;
            }   
            else {
                break;
            }
        }
        clearScreen();
        drawScreen();
        printf("\n  Invalid input.\n");
    }
    return input;
}

void delay(double time) {
    clock_t clockStart = clock();
    while(clock()<clockStart+time) {
        //Loops until number of milliseconds has passed
    }
    return;
}

void updateScreen(int player, int boardNum) {
    if(player==1) {
        board[boardNum] = 1;
    }
    else if(player==2) {
        board[boardNum] = 2;
    }
    system("cls");
    drawScreen();
}

int checkBoard(int player) {
    int num;
    // Checks Row for three in row for player
    for (int r = 0; r < 3; r++) {
        num = 0;
        for (int c = 0; c < 3; c++) {
            if (board[(r*3)+c]==player) 
                num++;
            if (num >= 3) 
                return player;
        }
    }
    // Checks Column for three in row for player
    for (int c = 0; c < 3; c++) {
        num = 0;
        for (int r = 0; r <3; r++) {
            if (board[(r*3)+c]==player) 
                num++;
            if (num >= 3) 
                return player;
        }
    }
    // Checks Diagonal for three in row for player 
    num = 0;
    int k = 0;
    for (int i = 0; i < 3 ; i++) {
        k = i*4;
        if(board[k]==player)
            num++;
        if (num >= 3)
            return player;
    }
    num = 0;
    for (int i = 1; i < 4; i++) {
        k = i*2;
        if (board[k]==player) 
            num++;
        if (num >= 3)
            return player;
    }
    //Returns 0 if none of above coditions are met (No 3 in a rows in board)
    return 0;
}

//Computer makes a move based on the current board
void computerMove(int moves) {
    if(moves>=9)
        return;
    time_t t;
    srand((unsigned) time(&t));
    gameMoves++;
    int boardChoice[9] = {0,0,0,0,0,0,0,0,0};
    int player = 0, computer = 0;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            for (int c2 = 0; c2 < 3; c2++) {
                if (board[(r*3)+c2] == 1)
                    player++;
                if (board[(r*3)+c2] == 2) 
                    computer++;
            }
            boardChoice[r*3+c] += boardChoicePoint(player, computer);
            computer = 0;
            player = 0;
        }
    }
    for (int c = 0; c < 3; c++) {
        for (int r = 0; r < 3; r++) {
            for (int r2 = 0; r2 < 3; r2++) {
                if (board[(r2*3)+c] == 1)
                    player++;
                if (board[(r2*3)+c] == 2) 
                    computer++;
            }
            boardChoice[r*3+c] += boardChoicePoint(player, computer);
            computer = 0;
            player = 0;
        }
    }
    int k = 0, k2 = 0;
    for (int i = 0; i < 3; i++) {
        k = i*4;
            for (int i2 = 0; i2 < 3; i2++) {
                k2 = i2*4;
                if(board[k2] == 1)
                    player++;
                if (board[k2] == 2)
                    computer++;
            }
        boardChoice[k] += boardChoicePoint(player, computer);
        computer = 0;
        player = 0;
    }
    for (int i = 1; i < 4; i++) {
        k = i*2;
            for (int i2 = 1; i2 < 4; i2++) {
                k2 = i2*2;
                if(board[k2] == 1)
                    player++;
                if (board[k2] == 2)
                    computer++;
            }
        boardChoice[k] += boardChoicePoint(player, computer);
        computer = 0;
        player = 0;
    }
    for (int i = 0; i < 9; i++) {
        if (board[i] != 0)
            boardChoice[i] = 0;
    }
    int max = 0, maxes = 0;
    for (int i = 0; i < 9; i++) {
        if (boardChoice[i] > boardChoice[max]) {
            maxes = 0;
            max = i;
            i = 0;
        }
        if (boardChoice[i]==boardChoice[max])
            maxes++;
    } 
    int a = rand() % maxes+1;
    int b = 0;
    for (int i = 0; i < 9; i++) {
        if(boardChoice[i] == boardChoice[max])
            b++;
        if (b==a) {
            b=i;
            break;
        }
    }
    for (int i = 0; i<rand()%36+12; i++) {
        if ((i+12)%12==0) {
            system("cls");
            drawScreen();
            printf("  Computer is thinking");
        }
        else if(i%3==0) {
            printf(".");
            delay(250);
        }
    }
    if (moves == 0)
        updateScreen(2, ((rand() % 5)*2));
    else 
        updateScreen(2, b);
    return;
}

//Points are assigned to each compartment based on how good the move is for the computer
int boardChoicePoint(int player, int computer) {
    if (computer == 2) 
        return 32;
    if (player == 2)
        return 16;
    if (computer == 1 && player == 0)
        return 8;
    if (player == 1 && computer == 0)
        return 4;
    if (player == 0 && computer == 0)
        return 2;
    if (player + computer != 3 )
        return 1;
    return 0;
}
