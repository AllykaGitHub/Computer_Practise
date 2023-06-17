#include "AbstractGhostFactory.h"

Pinky* PinkyFactory::createGhost(float x, float y, float radius, Pacman* pPacman){
    return new Pinky(x, y, radius, pPacman);
}

Inky* InkyFactory::createGhost(float x, float y, float radius, Pacman* pPacman){
    return new Inky(x, y, radius, pPacman);
}

Clyde* ClydeFactory::createGhost(float x, float y, float radius, Pacman* pPacman){
    return new Clyde(x, y, radius, pPacman);
}

Blinky* BlinkyFactory::createGhost(float x, float y, float radius, Pacman* pPacman){
    return new Blinky(x, y, radius, pPacman);
}