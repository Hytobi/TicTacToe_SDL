#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "SDL2/SDL.h"

typedef enum { CROIX, ROND, EMPTY } Player;

typedef struct ui {
    SDL_Window *window;
    SDL_Renderer *renderer;

} userInterface;

#endif