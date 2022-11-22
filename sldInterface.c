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
    ui.window =
        SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 480, 480, SDL_WINDOW_SHOWN);
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
    SDL_RenderDrawLine(ui.renderer, x, y, x + 160, y + 160);
    SDL_RenderDrawLine(ui.renderer, x + 160, y, x, y + 160);
}
void drawCircle(userInterface ui, int x, int y) {
    // Pour l'instant je mets une croix bleu
    SDL_SetRenderDrawColor(ui.renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(ui.renderer, x, y, x + 160, y + 160);
    SDL_RenderDrawLine(ui.renderer, x + 160, y, x, y + 160);

    /*
     SDL_Texture *texture =
         SDL_CreateTexture(ui.renderer, SDL_PIXELFORMAT_RGBA8888,
                           SDL_TEXTUREACCESS_STREAMING, 200, 200);
     if (NULL == texture) RAGE_QUIT(ui, "SDL_CreateTexture");
     SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
     if (!format) RAGE_QUIT(ui, "SDL_AllocFormat");
     int pitch = 200 * sizeof(Uint32);
     Uint32 pixels[200][200] = {0};
     for (int i = 0; i < 200; i++)
         for (int j = 0; j < 200; j++)
             pixels[i][j] =
                 SDL_MapRGBA(format, (i * i + j * j < 60) ? 255 : 0, 0, 0, 0);
     SDL_UpdateTexture(texture, NULL, pixels, pitch);
     SDL_FreeFormat(format);
     SDL_RenderCopy(ui.renderer, texture, NULL, NULL);
     */
}

void updateBoard(userInterface ui, int x, int y, Player player) {
    if (player == CROIX) {
        drawCross(ui, x * 160, y * 160);
    } else if (player == ROND) {
        drawCircle(ui, x * 160, y * 160);
    }
    SDL_RenderPresent(ui.renderer);
}
