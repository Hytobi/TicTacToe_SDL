#include "sldInterface.h"

#include "rage.h"

void sdlInterface_printBoard(userInterface ui) {
    SDL_SetRenderDrawColor(ui.renderer, 255, 255, 255, 255);
    SDL_RenderClear(ui.renderer);
    SDL_SetRenderDrawColor(ui.renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(ui.renderer, 0, 160, 480, 160);
    SDL_RenderDrawLine(ui.renderer, 0, 320, 480, 320);
    SDL_RenderDrawLine(ui.renderer, 160, 0, 160, 480);
    SDL_RenderDrawLine(ui.renderer, 320, 0, 320, 480);
    SDL_RenderPresent(ui.renderer);
}

userInterface sdlInterface_init() {
    userInterface ui;
    ui.window = NULL, ui.renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        RAGE_QUIT(ui, "SDL_Init");
    }
    ui.window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, MAX_WINDOWS,
                                 MAX_WINDOWS, SDL_WINDOW_SHOWN);
    if (ui.window == NULL) {
        RAGE_QUIT(ui, "SDL_CreateWindow");
    }
    ui.renderer = SDL_CreateRenderer(ui.window, -1, 0);
    if (ui.renderer == NULL) {
        RAGE_QUIT(ui, "SDL_CreateRenderer");
    }
    // On affiche le plateau de jeu
    sdlInterface_printBoard(ui);
    return ui;
}

void drawCross(userInterface ui, int x, int y) {
    SDL_SetRenderDrawColor(ui.renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(ui.renderer, x, y, x + TIER, y + TIER);
    SDL_RenderDrawLine(ui.renderer, x + TIER, y, x, y + TIER);
}
void drawCircle(userInterface ui, int x, int y) {
    /*
        Pour l'instant je mets une croix bleu
        SDL_SetRenderDrawColor(ui.renderer, 0, 0, 255, 255);
        SDL_RenderDrawLine(ui.renderer, x, y, x + 160, y + 160);
        SDL_RenderDrawLine(ui.renderer, x + 160, y, x, y + 160);
    */
    SDL_SetRenderDrawColor(ui.renderer, 0, 0, 255, 255);
    int radus = TIER * 30;
    int midX = (2 * x + TIER) / 2;
    int midY = (2 * y + TIER) / 2;

    for (int i = y + 1; i < y + TIER - 1; i++) {
        for (int j = x + 1; j < x + TIER - 1; j++) {
            if ((midY - i) * (midY - i) + (midX - j) * (midX - j) < radus) {
                SDL_RenderDrawLine(ui.renderer, midX, midY, j, i);
            }
        }
    }
    SDL_SetRenderDrawColor(ui.renderer, 255, 255, 255, 255);
    radus = TIER * 28;
    for (int i = y + 1; i < y + TIER - 1; i++) {
        for (int j = x + 1; j < x + TIER - 1; j++) {
            if ((midY - i) * (midY - i) + (midX - j) * (midX - j) < radus) {
                SDL_RenderDrawLine(ui.renderer, midX, midY, j, i);
            }
        }
    }
}

void updateBoard(userInterface ui, int x, int y, Player player) {
    if (player == CROIX) {
        drawCross(ui, x * 160, y * 160);
    } else if (player == ROND) {
        drawCircle(ui, x * 160, y * 160);
    }
    SDL_RenderPresent(ui.renderer);
}
