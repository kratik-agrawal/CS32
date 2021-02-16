//Kratik Agrawal
//Proj 3


#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject{
    public:
        Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, int xSpeed, int ySpeed, bool alive):
    GraphObject(imageID, startX, startY, startDirection, size, depth), m_alive(alive), m_xSpeed(xSpeed), m_ySpeed(ySpeed){}
        virtual void doSomething() = 0;



        //bool collided(Actor& object); //still need to define
    private:
        bool m_alive;
        int m_xSpeed;
        int m_ySpeed;
    
};

class HealthActor: public Actor {
    public:
        HealthActor(int imageID, double startX, double startY, int startDirection, double size, int depth, int xSpeed, int ySpeed, bool alive, int initialHealth):Actor(imageID, startX, startY, startDirection, size, depth, xSpeed, ySpeed, alive), health(initialHealth){}
        bool isAlive() { return health != 0; }
        
    private:
        int health;
};

class GhostRacer: public HealthActor {
    public:
    GhostRacer(): HealthActor(IID_GHOST_RACER, 128, 32, 90, 4.0, 0, 0, 0, true, 100){}
    virtual void doSomething() {}
private:
    
};

#endif // ACTOR_H_
