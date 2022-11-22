#include "textInterface.h"

#include "rage.h"

userInterface textInterface_init() {
    userInterface ui;
    ui.window = NULL, ui.renderer = NULL;
    return ui;
}

void printBoard(Player board[3][3]) {
    printf("\033[H\033[2J");
    for (int i = 0; i < 3; i++) {
        if (i != 0) {
            printf("---+---+---\n");
        }
        for (int j = 0; j < 3; j++) {
            board[i][j] == EMPTY  ? printf("   ")
            : board[i][j] == ROND ? printf(" O ")
                                  : printf(" X ");
            (j == 2) ? printf("\n") : printf("|");
        }
    }
}