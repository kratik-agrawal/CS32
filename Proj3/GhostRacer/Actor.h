//Kratik Agrawal
//Proj 3


#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <algorithm>
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
        bool basicDoSomethingStuff();
        
    virtual bool isCollisionAvoidanceWorthy() const { return false; }
        
        //bool collided(Actor& object); //still need to define
    private:
        bool m_alive;
        int m_xSpeed;
        int m_ySpeed;
        StudentWorld* world;
    
};

class HealthActor: public Actor {
    public:
        HealthActor(StudentWorld* w, int imageID, double startX, double startY, int startDirection, double size, int depth, int xSpeed, int ySpeed, bool alive, int initialHealth, int movement):Actor(w, imageID, startX, startY, startDirection, size, depth, xSpeed, ySpeed, alive), health(initialHealth), movementPlan(movement){}
        virtual ~HealthActor() {}
        int getHealth() const { return health; }
        void heal(int amt) { health +=amt; if(health > 100) health = 100; }
        void decreaseHealth(int amount);
        int getMovementPlan() const { return movementPlan; }
        void setMovementPlan(int movementDistance) { movementPlan = movementDistance; }
        void updateMovementPlan();
        virtual bool isCollisionAvoidanceWorthy() const { return true; }
    private:
        int health;
        int movementPlan;
};

class GhostRacer: public HealthActor {
    public:
        GhostRacer(StudentWorld* w): HealthActor(w, IID_GHOST_RACER, 128, 32, 90, 4.0, 0, 0, 0, true, 100, 0), sprayCount(10){}
        virtual void doSomething();
        void spin();
        int getSprays() { return sprayCount; }
        void increaseSprays(int amt) { sprayCount += amt;}
    private:
        
        int sprayCount;
};

class ZombieCab: public HealthActor {
    public:
        ZombieCab(StudentWorld* w, double startX, double startY, int ySpeed): HealthActor(w, IID_ZOMBIE_CAB, startX, startY, 90, 4.0, 0, 0, ySpeed, true, 3, 0), damagedGR(false) {}
        bool getDamagedGR() const { return damagedGR; }
        void setDamagedGR(bool state) { damagedGR = state; }
        virtual void doSomething();
    private:
        bool damagedGR;
    
};


class Pedestrian: public HealthActor {
    public:
        Pedestrian(StudentWorld* w, int imageID, double startX, double startY, double size): HealthActor(w, imageID, startX, startY, 0, size, 0, 0, -4, true, 2, 0) {}
        virtual ~Pedestrian() {}
        
    private:
       
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


class HolyWaterProjectile: public Actor {
public:
    HolyWaterProjectile(StudentWorld* w, double startX, double startY, int startDirection): Actor(w, IID_HOLY_WATER_PROJECTILE, startX, startY, startDirection, 1.0, 1, 0,0, true), travelDistance(160) {}
    void decreaseMovementDistance(int amt);
    virtual void doSomething();
private:
    int travelDistance;
    
};


#endif // ACTOR_H_
