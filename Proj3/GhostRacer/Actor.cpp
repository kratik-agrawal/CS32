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

void HealthActor::updateMovementPlan() {
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

bool Actor::basicDoSomethingStuff(){
    double newY;
    double newX;
    this->determineNewXNewY(newX, newY);
    
    moveTo(newX, newY);
    
    setAlive(determineAlive());
    return determineAlive();

}

void GhostRacer::spin(){
    int randDirection = randInt(5,20);
    int posNeg = randInt(1,2);
    if(posNeg == 1){
        setDirection(getDirection() + randDirection);
        if(getDirection() > 120)
            setDirection(120);
    }else{
        setDirection(getDirection() - randDirection);
        if(getDirection() < 60)
            setDirection(60);
    }
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

//Zombie Cab Do Something
void ZombieCab::doSomething(){
    if(!getAlive())
        return;
    
    if(!basicDoSomethingStuff())
        return;
    
    setMovementPlan(getMovementPlan() - 1);
    if(getMovementPlan() > 0)
        return;
    setYSpeed(ySpeed() + randInt(-2, 2));
    setMovementPlan(randInt(4,32));
}


//Human Pedestrian Class
void HumanPedestrian::doSomething() {
    if(!getAlive())
        return;
    if(getWorld()->overlapGhostRacer(this) != nullptr){
        getWorld()->ghostRacerDies();
        return;
    }
    
    if(!basicDoSomethingStuff())
        return;
    updateMovementPlan();
    
}

void ZombiePedestrian::doSomething() {
    if(!getAlive())
        return;
    if(getWorld()->overlapGhostRacer(this) != nullptr){
        getWorld()->overlapGhostRacer(this)->decreaseHealth(5);
        decreaseHealth(2);
        return;
    }
    
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
    
    if(!basicDoSomethingStuff())
        return;
    
    updateMovementPlan();
    
    
}

void HealingGoodie::doSomething() {
    
    if(!basicDoSomethingStuff())
        return;
    if(getWorld()->overlapGhostRacer(this) != nullptr){
        getWorld()->overlapGhostRacer(this)->heal(10);
        setAlive(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(250);
        return;
    }
}

void HolyWaterGoodie::doSomething() {
    
    if(!basicDoSomethingStuff())
        return;
    if(getWorld()->overlapGhostRacer(this) != nullptr){
        getWorld()->overlapGhostRacer(this)->increaseSprays(10);
        setAlive(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(50);
        return;
    }
    
}
void SoulGoodie::doSomething() {
    
    if(!basicDoSomethingStuff())
        return;
    
    if(getWorld()->overlapGhostRacer(this) != nullptr){
        getWorld()->increaseSoulsSaved();
        setAlive(false);
        getWorld()->playSound(SOUND_GOT_SOUL);
        getWorld()->increaseScore(100);
    }
        
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
    
    if(!basicDoSomethingStuff())
        return;
    
    if(getWorld()->overlapGhostRacer(this) != nullptr){
        getWorld()->playSound(SOUND_OIL_SLICK);
        getWorld()->overlapGhostRacer(this)->spin();
    }
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
//
//// Generate new Zombie Cab
//    int chanceVehicle = max(100 - (getLevel() * 10), 20);
//
//    if (randInt(0, chanceVehicle - 1) == 0) {
//        int curLane = randInt(0, 2);
//        bool laneFound = false;
//        int cabStartY = -999;
//        int cabSpeed = -999;
//        int laneCenter = -999;
//
//        bool checkedLeft = false;
//        bool checkedMid = false;
//        bool checkedRight = false;
//
//        while (!checkedLeft || !checkedMid || !checkedRight) {
//            int laneLeft = LEFT_EDGE + (curLane * (ROAD_WIDTH / 3));
//            int laneRight = LEFT_EDGE + (curLane + 1) * (ROAD_WIDTH / 3);
//
//            if ( !(gr->getX() >= laneLeft && gr->getX() < laneRight) ) {
//                int minY = 256;
//                Actor* a = nullptr;
//
//                for (unsigned long j = 0; j < Actors.size(); j++) {
//                    if (Actors.at(j)->getX() >= laneLeft &&
//                        Actors.at(j)->getX() < laneRight &&
//                        Actors.at(j)->getY() < minY &&
//                        Actors.at(j)->checkWorthy()) {
//
//                        a = Actors.at(j);
//                        minY = a->getY();
//                    }
//                }
//
//                if (a == nullptr || a->getY() > VIEW_HEIGHT / 3) {
//                    cabStartY = SPRITE_HEIGHT / 2;
//                    cabSpeed = gr->getySpeed() + randInt(2, 4);
//                    laneCenter = ROAD_CENTER + (curLane - 1) * (ROAD_WIDTH / 3);
//
//                    laneFound = true;
//                    break;
//                }
//
//                int maxY = 0;
//                a = nullptr;
//
//                for (unsigned long j = 0; j < Actors.size(); j++) {
//                    if (Actors.at(j)->getX() >= laneLeft &&
//                        Actors.at(j)->getX() < laneRight &&
//                        Actors.at(j)->getY() > maxY &&
//                        Actors.at(j)->checkWorthy()) {
//
//                        a = Actors.at(j);
//                        maxY = a->getY();
//                    }
//                }
//
//                if (a == nullptr || a->getY() < (2/3) * VIEW_HEIGHT) {
//                    cabStartY = VIEW_HEIGHT - SPRITE_HEIGHT / 2;
//                    cabSpeed = gr->getySpeed() - randInt(2, 4);
//                    laneCenter = ROAD_CENTER + (curLane - 1) * (ROAD_WIDTH / 3);
//
//                    laneFound = true;
//                    break;
//                }
//            }
//
//            switch (curLane) {
//                case 0:
//                    checkedLeft = true;
//
//                    if (!checkedMid) {
//                        curLane = 1;
//                    } else if (!checkedRight) {
//                        curLane = 2;
//                    }
//
//                    break;
//                case 1:
//                    checkedMid = true;
//
//                    if (!checkedLeft) {
//                        curLane = 0;
//                    } else if (!checkedRight) {
//                        curLane = 2;
//                    }
//
//                    break;
//                case 2:
//                    checkedRight = true;
//
//                    if (!checkedLeft) {
//                        curLane = 0;
//                    } else if(!checkedMid) {
//                        curLane = 1;
//                    }
//
//                    break;
//                default:
//                    break;
//            }
//        }
//
//        if (laneFound) {
//            Actors.push_back(new ZombieCab(laneCenter, cabStartY, cabSpeed, curLane, this, gr));
//        }
//    }
