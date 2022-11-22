#include "ticTacToe.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "SDL2/SDL.h"

ticTacToe* ticTacToe_init(Player player, int joueur) {
    ticTacToe* game = malloc(sizeof(ticTacToe));
    game->player = player;
    game->joueur = joueur;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // On met la grille à vide
            game->board[i][j] = EMPTY;
        }
    }
    return game;
}

// Vérife si le joueur a gagné
int estPartiePleine(Player board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Si on trouve une case vide, la partie n'est pas pleine
            if (board[i][j] == EMPTY) {
                return 0;
            }
        }
    }
    return 1;
}
// Vérifie si les coordonnées sont valides
int estDansTab(int l, int c) { return (l >= 0 && l < 3 && c >= 0 && c < 3); }

// Compte l'alignement de pions dans une direction donnée
int compteValeur(Player p[3][3], Player val, int lig, int col, int incL,
                 int incC) {
    int total = 1, l, c;
    l = lig + incL;
    c = col + incC;
    while (estDansTab(l, c)) {
        if (p[l][c] != val) return total;
        total++;
        l += incL;
        c += incC;
    }
    return total;
}

// Return le max de quatre entiers
int max(int a, int b, int c, int d) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    if (d > max) max = d;
    return max;
}

int cGagne(Player p[3][3], Player val, int lig, int col) {
    int h, v, dd, dg;
    // Horizontal
    h = compteValeur(p, val, lig, col, 0, 1) +
        compteValeur(p, val, lig, col, 0, -1) - 1;
    // Vertical
    v = compteValeur(p, val, lig, col, 1, 0) +
        compteValeur(p, val, lig, col, -1, 0) - 1;
    // Diagonale droite
    dd = compteValeur(p, val, lig, col, 1, 1) +
         compteValeur(p, val, lig, col, -1, -1) - 1;
    // Diagonale gauche
    dg = compteValeur(p, val, lig, col, 1, -1) +
         compteValeur(p, val, lig, col, -1, 1) - 1;

    return max(h, v, dd, dg);
}

int verifFinPartie(ticTacToe* game, int x, int y) {
    // Si le joueur a gagné
    if (cGagne(game->board, game->player, y, x) >= 3) {
        printf("%s a gagné\n", game->player == CROIX ? "X" : "O");
        sleep(5);
        return 1;
    }
    // Si la partie est pleine
    if (estPartiePleine(game->board)) {
        printf("Partie Nulle\n");
        return 1;
    }
    // Sinon on change de joueur
    game->player = game->player == CROIX ? ROND : CROIX;
    return 0;
}
// Fin vérifie si le joueur a gagné

// On joue
void playSDL(ticTacToe* game, userInterface ui) {
    int x, y, fini = 0;
    SDL_Event event;
    while (SDL_WaitEvent(&event) > 0 && !fini) {
        if (event.type == SDL_QUIT) break;
        if ((game->joueur == 2 && game->player == CROIX) || game->joueur == 3) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // On recupere les coordonnées de la souris
                SDL_GetMouseState(&x, &y);
                // coordonnées souris -> coordonnées tableau
                x /= 160;
                y /= 160;
                // On joue si la case est vide
                if (game->board[y][x] == EMPTY) {
                    // On joue le coup
                    game->board[y][x] = game->player;
                    // On met à jour l'affichage
                    updateBoard(ui, x, y, game->player);
                    // On vérifie si la partie est finie
                    fini = verifFinPartie(game, x, y);
                }
            }
        } else {
            // Sinon on joue un coup aléatoire
            srand(time(NULL));
            sleep(2);
            do {
                x = 0, y = 0;
                x = rand() % 3;
                y = rand() % 3;
            } while (game->board[x][y] != EMPTY);

            // On joue le coup
            game->board[x][y] = game->player;

            // On met à jour l'affichage
            updateBoard(ui, y, x, game->player);
            // On vérifie si la partie est finie
            fini = verifFinPartie(game, y, x);
        }
    }
}

void playText(ticTacToe* game) {
    int x, y, fini = 0;
    char c;
    // On affiche le tableau vide
    printBoard(game->board);
    while (!fini) {
        // Si c'est le tour d'un joueur humain
        if ((game->joueur == 2 && game->player == CROIX) || game->joueur == 3) {
            // Tant qu'on a pas de coord valide on demande
            do {
                printf("Entrez les coordonnées de votre coup : ");
                if (!scanf("%d %d", &x, &y)) {
                    while (c = getchar() != '\n' && c != EOF)
                        ;
                }
                if (game->board[x][y] != EMPTY) {
                    printf("Case déjà prise\n");
                }
            } while (!estDansTab(x, y) || game->board[x][y] != EMPTY);
        } else {
            // Sinon on joue un coup aléatoire
            srand(time(NULL));
            sleep(2);
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (game->board[x][y] != EMPTY);
        }
        // On joue le coup
        game->board[x][y] = game->player;
        // On affiche le tableau
        printBoard(game->board);
        // On regard si la partie est finie
        fini = verifFinPartie(game, x, y);
    }
}

void ticTacToe_playGame(ticTacToe* game, userInterface ui) {
    if (ui.renderer == NULL) {
        // Si y'a pas de renderer, on joue en mode texte
        playText(game);
    } else {
        // Sinon on joue en mode graphique
        playSDL(game, ui);
    }
}
// Fin on joue
