#include <stdio.h>

#include "sldInterface.h"
#include "textInterface.h"
#include "ticTacToe.h"
#include "userInterface.h"

int chooseInterface() {
    int choice;
    char c;
    do {
        printf("\033[H\033[2J");
        printf("Choose an interface:\n");
        printf("1. Text\n");
        printf("2. SDL\n");
        printf("3. Quitter\n\n");
        printf("Your choice: ");

        if (!scanf("%d", &choice)) {
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Choix invalide\n");
        }
    } while (choice < 1 || choice > 3);
    return choice;
}
int choosePlayer() {
    int choice;
    char c;
    do {
        printf("\033[H\033[2J");
        printf("Choose an interface:\n");
        printf("1. IA vs IA\n");
        printf("2. JOUEUR vs IA\n");
        printf("3. JOUEUR vs JOUEUR\n\n");
        printf("Your choice: ");

        if (!scanf("%d", &choice)) {
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Choix invalide\n");
        }
    } while (choice < 1 || choice > 3);
    return choice;
}

int main() {
    printf("[main] Tic-Tac-Toe\n");

    int joueur = choosePlayer();

    int choice = chooseInterface();
    if (choice == 3) return EXIT_SUCCESS;

    ticTacToe *game = ticTacToe_init(CROIX, joueur);
    userInterface ui;
    if (choice == 1)
        ui = textInterface_init();
    else if (choice == 2)
        ui = sdlInterface_init();
    ticTacToe_playGame(game, ui);

    // Pour l'instant pour bien fermer la fenêtre SDL
    if (NULL != ui.renderer) SDL_DestroyRenderer(ui.renderer);
    if (NULL != ui.window) SDL_DestroyWindow(ui.window);
    SDL_Quit();
    //

    return 0;
}  // main