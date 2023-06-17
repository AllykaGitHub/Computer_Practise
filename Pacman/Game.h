#pragma once

#include "Field.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Pacman.h"
#include "Entity.h"
#include "Cell.h"
#include "Ghost.h"
#include "AbstractGhostFactory.h"
#include "UIPanel.h"

class GameState;
class ActiveState;
class GameOverState;

class Game{
protected:
    UIPanel* uiPanel;
    Field game_field;

    GameState* currentGameState;
    ActiveState* activeState;
    GameOverState* gameOverState;

	std::vector<Entity*> objects;
	std::vector<Ghost*> ghosts;
	std::vector<Cell*> cells;
	Pacman *pacman;

public:
	Game();
	std::vector<Entity*> getEntities();
	std::vector<Cell*> getCells();
	Pacman getPacman();
	void updateGame(float elapsedTime); // изменения координат объектов
	void render(sf::RenderWindow& window) const; // отрисовка
	virtual ~Game();

    void setGameState(GameState* newState);
    ActiveState* getActiveState();
    GameOverState* getGameOverState();

    void endGame();
};


class GameState{
protected:
    Game* game;
public:
    explicit GameState(Game *pGame);
    virtual void endGame() = 0;
    virtual bool isGameOverState() = 0;
};

class ActiveState: public GameState{
public:
    explicit ActiveState(Game* pGame);
    void endGame() override;
    bool isGameOverState() override;
};

class GameOverState: public GameState{
public:
    explicit GameOverState(Game* pGame);
    void endGame() override;
    bool isGameOverState() override;
};

