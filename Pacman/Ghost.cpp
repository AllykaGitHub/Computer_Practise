#include "Ghost.h"
#include <iostream>

Ghost::Ghost(float x, float y, float radius, Pacman* pPacman): MovingEntity(x, y){
    is_chasing = false;
    ghost_radius = radius;

    houseMode = new HouseMode(this);
    chaseMode = new ChaseMode(this);
    scatterMode = new ScatterMode(this);
    eatenMode = new EatenMode(this);
    frightenedMode = new FrightenedMode(this);
    currentState = houseMode;

    strategy = nullptr;

    pacman = pPacman;
    is_chasing = false;
    is_dangerous = false;
    start_position = position;
}

Ghost::~Ghost(){
    delete houseMode;
    delete chaseMode;
    delete scatterMode;
    delete eatenMode;
    delete frightenedMode;
}

float Ghost::getRadius() const{
    return ghost_radius;
}

void Ghost::render(sf::RenderWindow &window){
    window.draw(shape);
}

void Ghost::setState(GhostState *newState){
    currentState = newState;
    currentState->setDangerousStatus();
}

void Ghost::setPacman(Pacman *pPacman){
    pacman = pPacman;
}

bool Ghost::isChasing() const{
    return is_chasing;
}

void Ghost::setChasingStatus(bool isChasing){
    is_chasing = isChasing;
}

void Ghost::setDangerousStatus(bool isDangerous){
    is_dangerous = isDangerous;
}

sf::Vector2f Ghost::get_position(){
    return position;
}

std::string Ghost::getCurrentStateInfo(){
    return currentState->getStateInfo();
}

HouseMode* Ghost::getHouseMode(){
    return houseMode;
}

ChaseMode* Ghost::getChaseMode(){
    return chaseMode;
}

ScatterMode* Ghost::getScatterMode(){
    return scatterMode;
}

EatenMode* Ghost::getEatenMode(){
    return eatenMode;
}

FrightenedMode* Ghost::getFrightenedMode(){
    return frightenedMode;
}

sf::Vector2f Ghost::getChasePosition(){
    return strategy->getChasePosition();
}

sf::Vector2f Ghost::getChaseScatterPosition(){
    return strategy->getChaseScatterPosition();
}

sf::FloatRect Ghost::getGlobalBounds() const{
    return shape.getGlobalBounds();
}


//GHOST STATE
GhostState::GhostState(Ghost* pGhost) {
    ghost = pGhost;
}
void GhostState::superPacGumEaten(){}
void GhostState::timerModeOver(){}
void GhostState::timerFrightenedMode(){}
void GhostState::eaten(){}
void GhostState::outsideHouse(){}
void GhostState::insideHouse(){}
void GhostState::computeNextDir(){}
sf::Vector2f GhostState::getTargetPosition(){
    return {0.0f, 0.0f};
};
void GhostState::setDangerousStatus(){};
std::string GhostState::getStateInfo() {
    return "";
};


//HOUSE MODE
HouseMode::HouseMode(Ghost* pGhost): GhostState(pGhost){}
void HouseMode::outsideHouse(){
    if (ghost->isChasing()){
        ghost->setState(ghost->getChaseMode());
        return;
    }
    ghost->setState(ghost->getScatterMode());
}
sf::Vector2f HouseMode::getTargetPosition(){
    return {0.0f, 0.0f};
}
void HouseMode::setDangerousStatus(){
    ghost->setDangerousStatus(false);
}
std::string HouseMode::getStateInfo(){
    return "HouseMode";
}


//CHASE MODE
ChaseMode::ChaseMode(Ghost* pGhost): GhostState(pGhost){}
void ChaseMode::superPacGumEaten(){
    ghost->setState(ghost->getFrightenedMode());
}
void ChaseMode::timerModeOver(){
    ghost->setState(ghost->getScatterMode());
}
sf::Vector2f ChaseMode::getTargetPosition(){
    return ghost->getChasePosition();
}
void ChaseMode::setDangerousStatus(){
    ghost->setDangerousStatus(true);
}
std::string ChaseMode::getStateInfo(){
    return "ChaseMode";
}


//SCATTER MODE
ScatterMode::ScatterMode(Ghost* pGhost): GhostState(pGhost){}
void ScatterMode::superPacGumEaten(){
    ghost->setState(ghost->getFrightenedMode());
}
void ScatterMode::timerModeOver(){
    ghost->setState(ghost->getChaseMode());
}
sf::Vector2f ScatterMode::getTargetPosition(){
    return ghost->getChaseScatterPosition();
}
void ScatterMode::setDangerousStatus(){
    ghost->setDangerousStatus(false);
}
std::string ScatterMode::getStateInfo(){
    return "ScatterMode";
}



//EATEN MODE
EatenMode::EatenMode(Ghost* pGhost): GhostState(pGhost){}
void EatenMode::insideHouse(){
    ghost->setState(ghost->getHouseMode());
}
sf::Vector2f EatenMode::getTargetPosition(){
    return {0.0f, 0.0f};
}
void EatenMode::setDangerousStatus(){
    ghost->setDangerousStatus(false);
}
std::string EatenMode::getStateInfo(){
    return "EatenMode";
}



//FRIGHTENED MODE
FrightenedMode::FrightenedMode(Ghost* pGhost): GhostState(pGhost){};
void FrightenedMode::timerFrightenedMode(){
    if (ghost->isChasing()){
        ghost->setState(ghost->getChaseMode());
        return;
    }
    ghost->setState(ghost->getScatterMode());
}
void FrightenedMode::eaten(){
    ghost->setState(ghost->getEatenMode());
}
sf::Vector2f FrightenedMode::getTargetPosition(){
    return {0.0f, 0.0f};
}
void FrightenedMode::setDangerousStatus(){
    ghost->setDangerousStatus(true);
}
std::string FrightenedMode::getStateInfo(){
    return "FrightenedMode";
}


//DIFFERENT GHOSTS TYPES
Blinky::Blinky(float x, float y, float radius, Pacman* pPacman): Ghost(x, y, radius, pPacman){
    strategy = new BlinkyStrategy(pPacman, this);
    color = sf::Color::Red;

    shape.setFillColor(color);
    shape.setRadius(radius);
    shape.setPosition(position);
}
Blinky::~Blinky(){
    delete strategy;
}
void Blinky::updatePosition(float elapsedTime){
    position += sf::Vector2f(0.1f, 0.3f);
}


Clyde::Clyde(float x, float y, float radius, Pacman* pPacman): Ghost(x, y, radius, pPacman){
    strategy = new ClydeStrategy(pPacman, this);
    color = sf::Color(250, 179, 26);

    shape.setFillColor(color);
    shape.setRadius(radius);
    shape.setPosition(position);
}
Clyde::~Clyde(){
    delete strategy;
}
void Clyde::updatePosition(float elapsedTime){
    position += sf::Vector2f(0.1f, 0.2f);
}


Inky::Inky(float x, float y, float radius, Pacman* pPacman): Ghost(x, y, radius, pPacman){
    strategy = new InkyStrategy(pPacman, this);
    color = sf::Color(26, 250, 216);

    shape.setFillColor(color);
    shape.setRadius(radius);
    shape.setPosition(position);
}
Inky::~Inky(){
    delete strategy;
}
void Inky::updateBlinky(Blinky *other) {
    delete strategy;
    strategy = new InkyStrategy(pacman, this, other);
}
void Inky::updatePosition(float elapsedTime){
    position += sf::Vector2f(0.2f, 0.2f);
}


Pinky::Pinky(float x, float y, float radius, Pacman* pPacman): Ghost(x, y, radius, pPacman){
    strategy = new PinkyStrategy(pPacman, this);
    color = sf::Color::Magenta;

    shape.setFillColor(color);
    shape.setRadius(radius);
    shape.setPosition(position);
}
Pinky::~Pinky(){
    delete strategy;
}
void Pinky::updatePosition(float elapsedTime){
    position += sf::Vector2f(0.3f, 0.3f);
}



/*--------------------------------------------------------------*/
GhostStrategy::GhostStrategy(Pacman *pPacman, Ghost* pGhost){
    pacman = pPacman;
    ghost = pGhost;
}


//ClydeStrategy
ClydeStrategy::ClydeStrategy(Pacman *pPacman, Ghost* pGhost):
        GhostStrategy(pPacman, pGhost){};

sf::Vector2f ClydeStrategy::getChasePosition(){
    sf::Vector2f vec = (ghost->get_position() - pacman->getPacmanPosition());
    if (vec.x * vec.x + vec.y + vec.y <= 200){
        return pacman->getPacmanPosition();
    }
    return getChaseScatterPosition();

}

sf::Vector2f ClydeStrategy::getChaseScatterPosition(){
    return Field::lower_left;
}


//BlinkyStrategy
BlinkyStrategy::BlinkyStrategy(Pacman *pPacman, Ghost* pGhost):
        GhostStrategy(pPacman, pGhost){};

sf::Vector2f BlinkyStrategy::getChasePosition() {
    return pacman->getPacmanPosition();
}
sf::Vector2f BlinkyStrategy::getChaseScatterPosition(){
    return Field::upper_right;
}


//PinkyStrategy
PinkyStrategy::PinkyStrategy(Pacman *pPacman, Ghost *pGhost):
        GhostStrategy(pPacman, pGhost){};

sf::Vector2f PinkyStrategy::getChasePosition(){
    auto pacman_vec = pacman->getPacmanPosition();
    if (pacman_vec.x - 2 * Field::block_size > 0){
        return {pacman_vec.x - 2 * Field::block_size, pacman_vec.y};
    }
    if (pacman_vec.y - 2 * Field::block_size > 0){
        return {pacman_vec.x, pacman_vec.y - 2 * Field::block_size};
    }
    return {pacman_vec.x + 2 * Field::block_size, pacman_vec.y};
}

sf::Vector2f PinkyStrategy::getChaseScatterPosition(){
    return Field::upper_left;
}


//InkyStrategy
InkyStrategy::InkyStrategy(Pacman *pPacman, Ghost *pGhost, Blinky* pBlinky):
        GhostStrategy(pPacman, pGhost){
    blinky = pBlinky;
};

sf::Vector2f InkyStrategy::getChasePosition() {
    auto dir = pacman->getPacmanDirection();
    sf::Vector2f vec = pacman->getPacmanPosition();
    if (dir == Direction::UP){
        vec.y -= Field::block_size * 2;
    }
    if (dir == Direction::DOWN){
        vec.y += Field::block_size * 2;
    }
    if (dir == Direction::RIGHT){
        vec.x += Field::block_size * 2;
    }
    if (dir == Direction::LEFT){
        vec.x -= Field::block_size * 2;
    }
    if (blinky != nullptr){
        vec -= blinky->get_position();
    }

    vec.x *= 2;
    vec.y *= 2;

    return vec;
}

sf::Vector2f InkyStrategy::getChaseScatterPosition() {
    float radius = ghost->getRadius();
    return Field::lower_right;
}

bool PacmanChecker::isPacmanCollide(const Pacman *pacman, const std::vector<Ghost *> ghosts) {
    for (auto ghost: ghosts){
        if (ghost->getGlobalBounds().intersects(pacman->getGlobalBounds())){
            return true;
        }
    }
    return false;
}
