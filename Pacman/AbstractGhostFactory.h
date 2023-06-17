#pragma once
#include "Ghost.h"

class AbstractGhostFactory{
public:
    virtual Ghost* createGhost(float x, float y, float size, Pacman* pPacman) = 0;
};

class PinkyFactory: public AbstractGhostFactory{
public:
    Pinky* createGhost(float x, float y, float radius, Pacman* pPacman) override;
};

class InkyFactory: public AbstractGhostFactory{
public:
    Inky* createGhost(float x, float y, float radius, Pacman* pPacman) override;
};

class ClydeFactory: public AbstractGhostFactory{
public:
    Clyde* createGhost(float x, float y, float radius, Pacman* pPacman) override;
};

class BlinkyFactory: public AbstractGhostFactory{
public:
    Blinky* createGhost(float x, float y, float radius, Pacman* pPacman) override;
};

