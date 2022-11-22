#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "sldInterface.h"
#include "textInterface.h"
#include "userInterface.h"

typedef struct {
    Player board[3][3];
    Player player;
    int joueur;
} ticTacToe;

ticTacToe* ticTacToe_init(Player player, int joueur);
void ticTacToe_playGame(ticTacToe* game, userInterface ui);

#endif