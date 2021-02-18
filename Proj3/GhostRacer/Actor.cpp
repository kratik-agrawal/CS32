//Kratik Agrawal
//Proj 3

#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp



//GhostRacer Class
void GhostRacer::doSomething(){
    //check if alive
    
    
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
    double new_y = getY() + ySpeed() - getWorld()->getGhostRacer()->ySpeed();
    double new_x = getX() + xSpeed();
    
    moveTo(new_x, new_y);
    
    if(getY() < 0 || getX() < 0 || getY() > VIEW_HEIGHT || getX() > VIEW_WIDTH)
        setAlive(false);
    
}
