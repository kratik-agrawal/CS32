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

void HealthActor::decreaseHealth(int amount){
    health -= amount;
    if(health <= 0){
        setAlive(false);
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
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

void Actor::basicDoSomethingStuff(){
    double newY;
    double newX;
    this->determineNewXNewY(newX, newY);
    
    moveTo(newX, newY);
    
    setAlive(determineAlive());

}


//GhostRacer Class
void GhostRacer::doSomething(){
    //check if alive
    if(!getAlive())
        return;
    
    if(getX() <= LEFT_EDGE_BORDER){
        if(getDirection() > 90){
            decreaseHealth(10);
            setDirection(82);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
        }
    }else if(getX() >= RIGHT_EDGE_BORDER){
        if(getDirection() < 90){
            decreaseHealth(10);
            setDirection(98);
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
        }
    } else {
        //take input and update Ghost Racer accordingly
        int ch;
        if(getWorld()->getKey(ch)){
            switch(ch){
                case KEY_PRESS_SPACE:
                    if(sprayCount > 0){
                        double projectileX = getX() + cos(abs(getDirection())*M_PI/180)*SPRITE_HEIGHT;
                        double projectileY = getY() - sin(abs(getDirection())*M_PI/180)*SPRITE_HEIGHT;
                        
                          getWorld()->addWaterProjectile(projectileX, projectileY, getDirection());
                        getWorld()->playSound(SOUND_PLAYER_SPRAY);
                        sprayCount--;
                    }
                    break;
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
                
            }
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
    
    basicDoSomethingStuff();
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
    
    basicDoSomethingStuff();
    updateMovementPlan();
    
    
}

void HealingGoodie::doSomething() {
    
    basicDoSomethingStuff();
    
}

void HolyWaterGoodie::doSomething() {
    
    basicDoSomethingStuff();
    
}
void SoulGoodie::doSomething() {
    
    basicDoSomethingStuff();
    
    //Rotate clockwise 10 degreesxs7354
    if(getDirection() > 10)
        setDirection(getDirection()-10);
    else if(getDirection() == 0)
        setDirection(350);
    else{
        int degreesSpillOver = 10%getDirection();
        setDirection(359-degreesSpillOver+1);
    }
}

void OilSlick::doSomething() {
    
    basicDoSomethingStuff();
    
}

void HolyWaterProjectile::decreaseMovementDistance(int amt){
    travelDistance -= amt;
    if(travelDistance <= 0)
        setAlive(false);
}
void HolyWaterProjectile::doSomething(){
    if(!getAlive())
        return;
    
    moveForward(SPRITE_HEIGHT);
    determineAlive();
    decreaseMovementDistance(SPRITE_HEIGHT);
}
