//Kratik Agrawal
//Proj 3


#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor: public GraphObject{
    public:
        Actor(StudentWorld* w, int imageID, double startX, double startY, int startDirection, double size, int depth, int xSpeed, int ySpeed, bool alive):
        world(w), GraphObject(imageID, startX, startY, startDirection, size, depth), m_alive(alive), m_xSpeed(xSpeed), m_ySpeed(ySpeed){}
        virtual ~Actor() {}
        virtual void doSomething() = 0;
        int ySpeed() const { return m_ySpeed; }
        int xSpeed() const { return m_xSpeed; }
        void setXSpeed(int x) { m_xSpeed = x; }
        void setYSpeed(int y) { m_ySpeed = y; }
        bool getAlive() const { return m_alive; }
        void setAlive(bool state) { m_alive = state; }
        void determineNewXNewY(double &newX, double &newY);
        bool determineAlive() const;
        StudentWorld* getWorld() { return world; }
        void basicDoSomethingStuff();
        
        //bool collided(Actor& object); //still need to define
    private:
        bool m_alive;
        int m_xSpeed;
        int m_ySpeed;
        StudentWorld* world;
    
};

class HealthActor: public Actor {
    public:
        HealthActor(StudentWorld* w, int imageID, double startX, double startY, int startDirection, double size, int depth, int xSpeed, int ySpeed, bool alive, int initialHealth):Actor(w, imageID, startX, startY, startDirection, size, depth, xSpeed, ySpeed, alive), health(initialHealth){}
        virtual ~HealthActor() {}
        int getHealth() const { return health; }
        void decreaseHealth(int amount);   
    private:
        int health;
};

class GhostRacer: public HealthActor {
    public:
        GhostRacer(StudentWorld* w): HealthActor(w, IID_GHOST_RACER, 128, 32, 90, 4.0, 0, 0, 0, true, 100), sprayCount(10){}
        virtual void doSomething();
        
    private:
        
        int sprayCount;
};


class Pedestrian: public HealthActor {
    public:
        Pedestrian(StudentWorld* w, int imageID, double startX, double startY, double size): HealthActor(w, imageID, startX, startY, 0, size, 0, 0, -4, true, 2), movementPlan(0) {}
        virtual ~Pedestrian() {}
        int getMovementPlan() const { return movementPlan; }
        void setMovementPlan(int movementDistance) { movementPlan = movementDistance; }
        void updateMovementPlan();
    private:
        int movementPlan;
};

class HumanPedestrian: public Pedestrian {
    public:
        HumanPedestrian(StudentWorld* w, double startX, double startY): Pedestrian(w, IID_HUMAN_PED, startX, startY, 2.0) {}
        virtual void doSomething();
};

class ZombiePedestrian: public Pedestrian {
    public:
        ZombiePedestrian(StudentWorld* w, double startX, double startY): Pedestrian(w, IID_ZOMBIE_PED, startX, startY, 3.0), ticksTillGrunt(0) {}
        int getTicksTillGrunt() const {  return ticksTillGrunt; }
        void setTicksTillGrunt(int ticks) { ticksTillGrunt = ticks; }
        virtual void doSomething();
    private:
        int ticksTillGrunt;
};

class BorderLine: public Actor {
    public:
        BorderLine(StudentWorld* w, int imageID, double startX, double startY): Actor(w, imageID, startX, startY, 0, 2.0, 2, 0, -4, true) {}
        virtual void doSomething();
    private:
    
};

class Goodies: public Actor {
    public:
        Goodies(StudentWorld* w, int imageID, double startX, double startY, int startDirection, double size): Actor(w, imageID, startX, startY, startDirection, size, 2, 0, -4, true) {}
    virtual ~Goodies() {}
    private:
    
};

class HealingGoodie: public Goodies {
    public:
        HealingGoodie(StudentWorld* w, double startX, double startY): Goodies(w, IID_HEAL_GOODIE, startX, startY, 0, 1.0) {}
        virtual void doSomething();
};
class HolyWaterGoodie: public Goodies {
    public:
        HolyWaterGoodie(StudentWorld* w, double startX, double startY): Goodies(w, IID_HOLY_WATER_GOODIE, startX, startY, 90, 2.0) {}
        virtual void doSomething();
};
class SoulGoodie: public Goodies {
    public:
        SoulGoodie(StudentWorld* w, double startX, double startY): Goodies(w, IID_SOUL_GOODIE, startX, startY, 0, 4.0) {}
        virtual void doSomething();
};

class OilSlick: public Actor {
    public:
        OilSlick(StudentWorld* w, double startX, double startY): Actor(w, IID_OIL_SLICK , startX, startY, 0, randInt(2,5), 2, 0, -4, true) {}
        virtual void doSomething();
    private:
    
};

//int startDirection, double size, int depth, int xSpeed, int ySpeed, bool alive

class HolyWaterProjectile: public Actor {
public:
    HolyWaterProjectile(StudentWorld* w, double startX, double startY, int startDirection): Actor(w, IID_HOLY_WATER_PROJECTILE, startX, startY, startDirection, 1.0, 1, 0,0, true), travelDistance(160) {}
    void decreaseMovementDistance(int amt);
    virtual void doSomething();
private:
    int travelDistance;
    
};


#endif // ACTOR_H_
