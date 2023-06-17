#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include "Field.h"
#include "Pacman.h"
#include "Entity.h"

class GhostState;
class HouseMode;
class ChaseMode;
class ScatterMode;
class EatenMode;
class FrightenedMode;

class GhostStrategy;
class ClydeStrategy;
class BlinkyStrategy;
class PinkyStrategy;
class InkyStrategy;



class Ghost: public MovingEntity{
public:
    Ghost(float x, float y, float radius, Pacman* pPacman);
    ~Ghost() override;
    void render(sf::RenderWindow &window) override;
    float getRadius() const;
    void setState(GhostState* newState);
    void setPacman(Pacman* pPacman);
    bool isChasing() const;
    void setChasingStatus(bool isChasing);
    void setDangerousStatus(bool isDangerous);
    sf::Vector2f get_position();
    std::string getCurrentStateInfo();

    HouseMode* getHouseMode();
    ChaseMode* getChaseMode();
    ScatterMode* getScatterMode();
    EatenMode* getEatenMode();
    FrightenedMode* getFrightenedMode();

    sf::Vector2f getChasePosition();
    sf::Vector2f getChaseScatterPosition();
    sf::FloatRect getGlobalBounds() const;
    

protected:
    Pacman* pacman;

    GhostState* currentState;
    HouseMode* houseMode;
    ChaseMode* chaseMode;
    ScatterMode* scatterMode;
    EatenMode* eatenMode;
    FrightenedMode* frightenedMode;

    GhostStrategy* strategy;

    bool is_dangerous;
    bool is_chasing;
    sf::Color color;
    const float ghost_speed = 90.f;
    float ghost_radius;
    sf::Vector2f start_position;
};


class Blinky : public Ghost {
public:
    Blinky(float x, float y, float radius, Pacman* pPacman);
    ~Blinky() override;
    void updatePosition(float elapsedTime) override;
};

class Clyde : public Ghost {
public:
    Clyde(float x, float y, float radius, Pacman* pPacman);
    ~Clyde() override;
    void updatePosition(float elapsedTime) override;
};

class Inky : public Ghost {
public:
    Inky(float x, float y, float radius, Pacman* pPacman);
    ~Inky() override;
    void updateBlinky(Blinky* other);
    void updatePosition(float elapsedTime) override;
};

class Pinky : public Ghost {
public:
    Pinky(float x, float y, float radius, Pacman* pPacman);
    ~Pinky() override;
    void updatePosition(float elapsedTime) override;
};

class GhostState{
protected:
    Ghost* ghost;
public:
    explicit GhostState(Ghost* pGhost);
    virtual void superPacGumEaten();
    virtual void timerModeOver();
    virtual void timerFrightenedMode();
    virtual void eaten();
    virtual void outsideHouse();
    virtual void insideHouse();
    virtual void computeNextDir();
    virtual sf::Vector2f getTargetPosition();
    virtual void setDangerousStatus();
    virtual std::string getStateInfo();
};

class HouseMode: public GhostState{
public:
    explicit HouseMode(Ghost* pGhost);
    void outsideHouse() override;
    sf::Vector2f getTargetPosition() override;
    void setDangerousStatus() override;
    std::string getStateInfo() override;
};

class ChaseMode: public GhostState{
public:
    explicit ChaseMode(Ghost* pGhost);
    void superPacGumEaten() override;
    void timerModeOver() override;
    sf::Vector2f getTargetPosition() override;
    void setDangerousStatus() override;
    std::string getStateInfo() override;
};

class ScatterMode: public GhostState{
public:
    explicit ScatterMode(Ghost* pGhost);
    void superPacGumEaten() override;
    void timerModeOver() override;
    sf::Vector2f getTargetPosition() override;
    void setDangerousStatus() override;
    std::string getStateInfo() override;
};

class EatenMode: public GhostState{
public:
    explicit EatenMode(Ghost* pGhost);
    void insideHouse() override;
    sf::Vector2f getTargetPosition() override;
    void setDangerousStatus() override;
    std::string getStateInfo() override;
};

class FrightenedMode: public GhostState{
public:
    explicit FrightenedMode(Ghost* pGhost);
    void timerFrightenedMode() override;
    void eaten() override;
    sf::Vector2f getTargetPosition() override;
    void setDangerousStatus() override;
    std::string getStateInfo() override;
};


/*---------------------------------------------------------*/
class GhostStrategy{
protected:
    Pacman* pacman;
    Ghost* ghost;
public:
    explicit GhostStrategy(Pacman* pPacman, Ghost* pGhost);
    virtual sf::Vector2f getChasePosition() = 0;
    virtual sf::Vector2f getChaseScatterPosition() = 0;
    virtual ~GhostStrategy() = default;
};

class ClydeStrategy: public GhostStrategy{
public:
    ClydeStrategy(Pacman* pPacman, Ghost* pGhost);
    sf::Vector2f getChasePosition() override;
    sf::Vector2f getChaseScatterPosition() override;
};

class BlinkyStrategy: public GhostStrategy{
public:
    BlinkyStrategy(Pacman* pPacman, Ghost* pGhost);
    sf::Vector2f getChasePosition() override;
    sf::Vector2f getChaseScatterPosition() override;
};

class PinkyStrategy: public GhostStrategy{
public:
    PinkyStrategy(Pacman* pPacman, Ghost* pGhost);
    sf::Vector2f getChasePosition() override;
    sf::Vector2f getChaseScatterPosition() override;
};

class InkyStrategy: public GhostStrategy{
protected:
    Blinky* blinky;
public:
    InkyStrategy(Pacman* pPacman, Ghost* pGhost, Blinky* pBlinky = nullptr);
    sf::Vector2f getChasePosition() override;
    sf::Vector2f getChaseScatterPosition() override;
};


class PacmanChecker{
public:
    bool isPacmanCollide(const Pacman* pacman, std::vector<Ghost*> ghosts);
};