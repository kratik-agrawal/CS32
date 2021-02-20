//Kratik Agrawal
//Proj 3

#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actor Auxillary Functions
void Actor::determineNewXNewY(double &newX, double &newY){
    newY = getY() + ySpeed() - getWorld()->getGhostRacer()->ySpeed();
    newX = getX() + xSpeed();
}
bool Actor::determineAlive() const {
    if(getY() < 0 || getX() < 0 || getY() > VIEW_HEIGHT || getX() > VIEW_WIDTH)
        return false;
    return true;
}

void Pedestrian::updateMovementPlan() {
    setMovementPlan(getMovementPlan() - 1);
    if(getMovementPlan() > 0)
        return;
    setXSpeed(randInt(-3, 3));
    while(xSpeed() == 0)
        setXSpeed(randInt(-3, 3));
    setMovementPlan(randInt(4,32));
    if(xSpeed() > 0)
        setDirection(0);
    else
        setDirection(180);
}

//GhostRacer Class
void GhostRacer::doSomething(){
    //check if alive
    if(!getAlive())
        return;
    
    //take input and update Ghost Racer accordingly
    int ch;
    if(getWorld()->getKey(ch)){
        switch(ch){
            case KEY_PRESS_LEFT:
                if(getDirection() < 114)
                    setDirection(getDirection() + 8);
                break;
            case KEY_PRESS_RIGHT:
                if(getDirection() > 66)
                    setDirection(getDirection() - 8);
                break;
            case KEY_PRESS_UP:
                if(ySpeed() < 5)
                    setYSpeed(ySpeed()+1);
                break;
            case KEY_PRESS_DOWN:
                if(ySpeed() > -1)
                    setYSpeed(ySpeed()-1);
                break;
            case KEY_PRESS_SPACE:
                sprayCount--;
                break;
        }
    }
    
    //Movement Algorithm
    double MAX_SHIFT = 4.0;
    int direction = getDirection();
    double deltaX = cos(direction/180.0 * M_PI);
    deltaX *= MAX_SHIFT;
    moveTo(getX() + deltaX, getY());

}

//BorderLine Class
void BorderLine::doSomething() {
    double newY;
    double newX;
    this->determineNewXNewY(newX, newY);
    
    moveTo(newX, newY);
    
    setAlive(determineAlive());
    
}


//Human Pedestrian Class
void HumanPedestrian::doSomething() {
    if(!getAlive())
        return;
    double newY;
    double newX;
    this->determineNewXNewY(newX, newY);
    
    moveTo(newX, newY);
    
    setAlive(determineAlive());
    
    updateMovementPlan();
    
}

void ZombiePedestrian::doSomething() {
    if(!getAlive())
        return;
    
    if(getX() < getWorld()->getGhostRacer()->getX() + 30 && getX() > getWorld()->getGhostRacer()->getX() - 30 && getY() > getWorld()->getGhostRacer()->getY()){
        setDirection(270);
        if(getX() < getWorld()->getGhostRacer()->getX())
            setXSpeed(1);
        else if( getX() > getWorld()->getGhostRacer()->getX() )
            setXSpeed(-1);
        else
            setXSpeed(0);
        setTicksTillGrunt(getTicksTillGrunt()-1);
        if(getTicksTillGrunt() <= 0){
            getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
            setTicksTillGrunt(20);
        }
        
    }
    
    double newY;
    double newX;
    this->determineNewXNewY(newX, newY);
    
    moveTo(newX, newY);
    
    setAlive(determineAlive());
    
    updateMovementPlan();
    
}

