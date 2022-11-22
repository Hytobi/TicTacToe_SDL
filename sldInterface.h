#ifndef SLDINTERFACE_H
#define SLDINTERFACE_H

#include "SDL2/SDL.h"
#include "userInterface.h"

userInterface sdlInterface_init();
void updateBoard(userInterface ui, int x, int y, Player player);
#endif