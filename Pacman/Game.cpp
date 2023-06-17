#include <iostream>
#include "Game.h"
#include "AbstractGhostFactory.h"

Game::Game() {
    ClydeFactory clydeFactory;
    PinkyFactory pinkyFactory;
    BlinkyFactory blinkyFactory;
    InkyFactory inkyFactory;

    Clyde* new_clyde = nullptr;
    Pinky* new_pinky = nullptr;
    Blinky* new_blinky = nullptr;
    Inky* new_inky = nullptr;

    pacman = new Pacman(0, 0);

    float bs = Field::f_block_size;
    float ghost_size = pacman->getPacmanRadius();

    for (size_t i = 0; i < Field::height; i++){
        for (size_t j = 0; j < Field::width; j++){
            if (game_field.maze[i][j] == 'P'){
                new_pinky = pinkyFactory.createGhost(bs * j + 2.0f, bs * i + 2.0f, ghost_size, pacman);
                ghosts.push_back(new_pinky);
            }
            if (game_field.maze[i][j] == 'B'){
                new_blinky = blinkyFactory.createGhost(bs * j + 2.0f, bs * i + 2.0f, ghost_size, pacman);
                ghosts.push_back(new_blinky);
            }
            if (game_field.maze[i][j] == 'C'){
                new_clyde = clydeFactory.createGhost(bs * j, bs * i + 2.0f, ghost_size, pacman);
                ghosts.push_back(new_clyde);
            }
            if (game_field.maze[i][j] == 'I'){
                new_inky = inkyFactory.createGhost(bs * j + 2.0f, bs * i, ghost_size, pacman);
                ghosts.push_back(new_inky);
            }
            if (game_field.maze[i][j] == '#'){
                cells.push_back(new Cell(bs * j, bs * i, bs, CellCategory::WALL));
            }
            if (game_field.maze[i][j] == 'M'){
                pacman->setPacmanPosition(bs * j, bs * i + 5.0f);
            }
            if (game_field.maze[i][j] == 'o'){
                objects.push_back(new PacGum(bs * j, bs * i, bs));
            }
            if (game_field.maze[i][j] == 'S'){
                objects.push_back(new SuperPacGum(bs * j, bs * i, bs));
            }
            if (game_field.maze[i][j] == 'T'){
                uiPanel = new UIPanel(bs * j, bs * i, bs);
            }
        }
    }

    activeState = new ActiveState(this);
    gameOverState = new GameOverState(this);
    currentGameState = activeState;


    // create factory AbstractGhostFactory* ghostFactory;
    // read the text file with maze and positions of entities
    //if x - create wall and add into walls
    //if P - create pacman, add into objects
    //if b/p/i/c - create factories
    //create ghosts and add them into objects and ghosts
    //if . - create PacGum into objects
    //if o - create SuperPacGum
    //if - - create GhostHouse 
}

std::vector<Entity*> Game::getEntities() {
    return objects;
}

std::vector<Cell*> Game::getCells() {
    return cells;
}

Pacman Game::getPacman() {
    return *pacman;
}

void Game::updateGame(float elapsedTime) {
    pacman->update(0.005, cells);
    uiPanel->increaseScore(1);

    PacmanChecker pc;
    if (pc.isPacmanCollide(pacman, ghosts)){
        uiPanel->resetScore();
        uiPanel->setGameOverText();
        endGame();
    }

    //for (auto ghost: ghosts){
    //    ghost->updatePosition(elapsedTime);
    //}
}
void Game::render(sf::RenderWindow& window) const {
    if (currentGameState->isGameOverState()){
        uiPanel->render(window);
        return;
    }

    for (auto cell: cells){
        cell->render(window);
    }
    for (auto object: objects){
        object->render(window);
    }
    for (auto ghost: ghosts){
        ghost->render(window);
    }
    pacman->render(window);
    uiPanel->render(window);
}

Game::~Game() {
    for (auto object: objects){
        delete object;
    }
    for (auto ghost: ghosts){
        delete ghost;
    }
    for (auto cell: cells){
        delete cell;
    }
    delete pacman;
    delete uiPanel;
    delete activeState;
    delete gameOverState;
}

void Game::setGameState(GameState *newState){
    currentGameState = newState;
}

ActiveState* Game::getActiveState() {
    return activeState;
}

GameOverState* Game::getGameOverState() {
    return gameOverState;
}

void Game::endGame() {
    currentGameState->endGame();
}




GameState::GameState(Game *pGame): game(pGame){};


ActiveState::ActiveState(Game *pGame): GameState(pGame){};
void ActiveState::endGame() {
    game->setGameState(game->getGameOverState());
}
bool ActiveState::isGameOverState() {
    return false;
}


GameOverState::GameOverState(Game *pGame): GameState(pGame) {};
void GameOverState::endGame() {};
bool GameOverState::isGameOverState() {
    return true;
}
