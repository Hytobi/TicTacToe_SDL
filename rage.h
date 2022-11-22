#ifndef RAGE_H
#define RAGE_H

#include "SDL2/SDL.h"

#define RAGE_QUIT(ui, msg)                                         \
    {                                                              \
        fprintf(stderr, "Erreur %s : %s", msg, SDL_GetError());    \
        if (NULL != ui.renderer) SDL_DestroyRenderer(ui.renderer); \
        if (NULL != ui.window) SDL_DestroyWindow(ui.window);       \
        SDL_Quit();                                                \
        exit(EXIT_FAILURE);                                        \
    }

#endif