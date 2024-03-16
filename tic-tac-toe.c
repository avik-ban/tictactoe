#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char computer = 'X';
char user = 'O';

struct move {
    int x;
    int y;
};

void boardInitialization(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '_';
        }
    }
}

void printBoard(char board[3][3]) {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

int checkValidmove(int coordx, int coordy, char board[3][3]) {
    if (coordx < 0 || coordx > 2 || coordy < 0 || coordy > 2) {
        return 1;
    }

    if (board[coordx][coordy] == user || board[coordx][coordy] == computer) {
        return 1;
    }

    return 0;
}

int checkWin(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '_') {
            printf("%c wins!\n", board[i][0]);
            return 1;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != '_') {
            printf("%c wins!\n", board[0][j]);
            return 1;
        }
    }

    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_') ||
        (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[2][0] != '_')) {
        printf("%c wins!\n", board[1][1]);
        return 1;
    }

    return 0;
}

int userPlay(char board[3][3]) {
    struct move play;
    play.x = -1;
    play.y = -1;

    printf("Select an row (0-2) and col (0-2) for (O)\n");
    printf("row: ");
    scanf("%d", &play.x);
    printf("col: ");
    scanf("%d", &play.y);

    if (checkValidmove(play.x, play.y, board) == 0) {
        board[play.x][play.y] = user;
    } else {
        printf("Not a valid move\n");
        userPlay(board);
    }

    return 0;
}

int compPlay(char board[3][3]) {
    struct move play;
    play.x = -1;
    play.y = -1;

    play.x = rand() % 3;
    play.y = rand() % 3;

    if (checkValidmove(play.x, play.y, board) == 0) {
        board[play.x][play.y] = computer;
    } else {
        compPlay(board);
    }

    return 0;
}

int firstPlayer() {
    char HorT;
    printf("Pick heads or tails (H/T) to play first: ");
    scanf(" %c", &HorT);
    // 0=head 1=tails
    srand(time(NULL));
    int num = rand() % 2;

    if (num == 0) {
        if (HorT == 'H') {
            printf("You (O) Start\n");
            return 0;
        } else {
            printf("Computer (X) Starts\n");
            return 1;
        }
    } else {
        if (HorT == 'T') {
            printf("You (O) Start\n");
            return 0;
        } else {
            printf("Computer (X) Starts\n");
            return 1;
        }
    }
}

int main() {
    char board[3][3];

    boardInitialization(board);

    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Rules are simple, 3 X's or O's in a row (vertical, horizontal and diagonal)\n");
    printBoard(board);

    int currentPlayer = firstPlayer();

    while (!checkWin(board)) {
        if (currentPlayer == 0) {
            printf("User's turn (O)\n");
            userPlay(board);
        } else {
            printf("Computer's turn (X)\n");
            compPlay(board);
        }

        printBoard(board);

        currentPlayer = (1 + currentPlayer) % 2;
    }

    return 0;
}