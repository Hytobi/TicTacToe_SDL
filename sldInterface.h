#ifndef SLDINTERFACE_H
#define SLDINTERFACE_H

#include "SDL2/SDL.h"
#include "userInterface.h"

#define MAX_WINDOWS 480
#define TIER MAX_WINDOWS / 3

userInterface sdlInterface_init();
void updateBoard(userInterface ui, int x, int y, Player player);
#endif